/*
   +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   Copyright (c) 2012 Synaptics, Inc.

   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to use,
   copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
   Software, and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.


   +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   */
#define SYNA_F34_SAMPLE_CODE
#define SHOW_PROGRESS

#include <linux/module.h>
#include <linux/delay.h>
#include <linux/hrtimer.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/jiffies.h>

#include <linux/syscalls.h>
#include <linux/uaccess.h>

#if defined(CONFIG_MACH_MSM8974_TIGERS_KR)
#include <linux/wakelock.h>
#endif

#include "lge_touch_core.h"
#include "touch_synaptics.h"


/*                                 */
unsigned short SynaF34DataBase;
unsigned short SynaF34QueryBase;
unsigned short SynaF01DataBase;
unsigned short SynaF01CommandBase;
unsigned short SynaF01QueryBase;

unsigned short SynaF34Reflash_BlockNum;
unsigned short SynaF34Reflash_BlockData;
unsigned short SynaF34ReflashQuery_BootID;
unsigned short SynaF34ReflashQuery_FlashPropertyQuery;
unsigned short SynaF34ReflashQuery_BlockSize;
unsigned short SynaF34ReflashQuery_FirmwareBlockCount;
unsigned short SynaF34ReflashQuery_ConfigBlockCount;

unsigned char SynaF01Query43Length;

unsigned short SynaFirmwareBlockSize;
unsigned short SynaFirmwareBlockCount;
unsigned long SynaImageSize;

unsigned short SynaConfigBlockSize;
unsigned short SynaConfigBlockCount;
unsigned long SynaConfigImageSize;

unsigned short SynaBootloadID;

unsigned short SynaF34_FlashControl;
unsigned short SynaF34_FlashStatus;

unsigned char *SynafirmwareImgData;
unsigned char *SynaconfigImgData;
unsigned char *SynalockImgData;
unsigned int SynafirmwareImgVersion;

unsigned char *my_image_bin;
unsigned long my_image_size;
u8	fw_image_config_id[5];

unsigned char * ConfigBlock;

void CompleteReflash(struct synaptics_ts_data *ts);
void SynaInitialize(struct synaptics_ts_data *ts);
void SynaReadFirmwareInfo(struct synaptics_ts_data *ts);
void SynaEnableFlashing(struct synaptics_ts_data *ts);
void SynaProgramFirmware(struct synaptics_ts_data *ts);
void SynaFinalizeReflash(struct synaptics_ts_data *ts);
unsigned int SynaWaitForATTN(int time,struct synaptics_ts_data *ts);
bool CheckTouchControllerType(struct synaptics_ts_data *ts);
/*                                                         */
void eraseAllBlock(struct synaptics_ts_data *ts);
void SynaUpdateConfig(struct synaptics_ts_data *ts);
void EraseConfigBlock(struct synaptics_ts_data *ts);

enum FlashCommand
{
	m_uF34ReflashCmd_FirmwareCrc        = 0x01,   //                        
	m_uF34ReflashCmd_FirmwareWrite      = 0x02,
	m_uF34ReflashCmd_EraseAll           = 0x03,
	m_uF34ReflashCmd_LockDown           = 0x04,   //                         
	m_uF34ReflashCmd_ConfigRead         = 0x05,
	m_uF34ReflashCmd_ConfigWrite        = 0x06,
	m_uF34ReflashCmd_EraseUIConfig      = 0x07,
	m_uF34ReflashCmd_Enable             = 0x0F,
	m_uF34ReflashCmd_QuerySensorID      = 0x08,
	m_uF34ReflashCmd_EraseBLConfig      = 0x09,
	m_uF34ReflashCmd_EraseDisplayConfig = 0x0A,
};

char SynaFlashCommandStr[0x0C][0x20] =
{
	"",
	"FirmwareCrc",
	"FirmwareWrite",
	"EraseAll",
	"LockDown",
	"ConfigRead",
	"ConfigWrite",
	"EraseUIConfig",
	"Enable",
	"QuerySensorID",
	"EraseBLConfig",
	"EraseDisplayConfig",
};

int FirmwareUpgrade (struct synaptics_ts_data *ts, const char* fw_path) {

	int ret = 0;
	int fd = -1;
	mm_segment_t old_fs = 0;
	struct stat fw_bin_stat;
	unsigned long read_bytes;

	if (unlikely(fw_path[0] != 0)) {
		old_fs = get_fs();
		set_fs(get_ds());

		fd = sys_open((const char __user *) fw_path, O_RDONLY, 0);
		if (fd < 0) {
			TOUCH_ERR_MSG("Can not read FW binary from %s\n", fw_path);
			ret = -EEXIST;
			goto read_fail;
		}
		ret = sys_newstat((char __user *) fw_path, (struct stat *)&fw_bin_stat);
		if (ret < 0) {
			TOUCH_ERR_MSG("Can not read FW binary stat from %s\n", fw_path);
			goto fw_mem_alloc_fail;
		}

		my_image_size = fw_bin_stat.st_size;
		my_image_bin = kzalloc(sizeof(char) * (my_image_size+1), GFP_KERNEL);
		if (my_image_bin == NULL) {
			TOUCH_ERR_MSG("Can not allocate  memory\n");
			ret = -ENOMEM;
			goto fw_mem_alloc_fail;
		}

		read_bytes = sys_read(fd, (char __user *)my_image_bin, my_image_size);

		/*              */
		*(my_image_bin+my_image_size) = 0xFF;

		TOUCH_INFO_MSG("Touch FW image read %ld bytes from %s\n", read_bytes, fw_path);

	} else {
		my_image_size = ts->fw_info.fw_size-1;
		my_image_bin = (unsigned char *)(&ts->fw_info.fw_start[0]);
	}

	CompleteReflash(ts);
	/*
                              
                  
                                                     
     
    */

	if (unlikely(fw_path[0] != 0))
		kfree(my_image_bin);

fw_mem_alloc_fail:
	sys_close(fd);
read_fail:
	set_fs(old_fs);

	return ret;
}



static int writeRMI(struct i2c_client *client, u8 uRmiAddress, u8 *data, unsigned int length)
{
	return touch_i2c_write(client, uRmiAddress, length, data);
}

static int readRMI(struct i2c_client *client, u8 uRmiAddress, u8 *data, unsigned int length)
{
	return touch_i2c_read(client, uRmiAddress, length, data);
}

bool CheckFlashStatus(struct synaptics_ts_data *ts, enum FlashCommand command)//      
{
	unsigned char uData = 0;
	//                                                                                    
	//            
	readRMI(ts->client, SynaF34_FlashStatus, &uData, 1);
	//                                                                                      

	//                        
	//                                                                                                           
	return !(uData & 0x3F);
}

void SynaImageParser(struct synaptics_ts_data *ts)//      
{

	//                 
	SynaImageSize = ( (unsigned int)my_image_bin[0x08] |
			(unsigned int)my_image_bin[0x09] <<8 |
			(unsigned int)my_image_bin[0x0A] <<16|
			(unsigned int)my_image_bin[0x0B] <<24);
	SynafirmwareImgData = (unsigned char *)((&my_image_bin[0]) + 0x100);
	SynaconfigImgData   = (unsigned char *)(SynafirmwareImgData + SynaImageSize);
	SynafirmwareImgVersion = (unsigned int)(my_image_bin[7]);

	switch (SynafirmwareImgVersion)
	{
		case 2:
			SynalockImgData = (unsigned char *)((&my_image_bin[0]) + 0xD0);
			break;
		case 3:
		case 4:
			SynalockImgData = (unsigned char *)((&my_image_bin[0]) + 0xC0);
			break;
		case 5:
		case 6:
			SynalockImgData = (unsigned char *)((&my_image_bin[0]) + 0xB0);
		default: break;
	}
}

void SynaBootloaderLock(struct synaptics_ts_data *ts)//      
{
	unsigned short lockBlockCount;
	unsigned char uData[2] = {0};
	unsigned short uBlockNum;
	enum FlashCommand cmd;

	if (my_image_bin[0x1E] == 0)
	{
		TOUCH_ERR_MSG( "Skip lockdown process with this .img\n");
		return;
	}
	//                                     
	readRMI(ts->client, (SynaF34QueryBase+ 1), &uData[0], 1);

	//                  
	if (uData[0] & 0x02)
	{
		TOUCH_ERR_MSG("Device unlocked. Lock it first...\n");
		//                                                                             
		//                                                                         
		switch (SynafirmwareImgVersion)
		{
			case 2:
				lockBlockCount = 3;
				break;
			case 3:
			case 4:
				lockBlockCount = 4;
				break;
			case 5:
			case 6:
				lockBlockCount = 5;
				break;
			default:
				lockBlockCount = 0;
				break;
		}

		//                                       
		//                                                                              
		//                                                                                
		//                                                                                  
		//                                      
		for (uBlockNum = 0; uBlockNum < lockBlockCount; ++uBlockNum)
		{
			uData[0] = uBlockNum & 0xff;
			uData[1] = (uBlockNum & 0xff00) >> 8;

			/*                    */
			writeRMI(ts->client, SynaF34Reflash_BlockNum, &uData[0], 2);

			/*                  */
			writeRMI(ts->client, SynaF34Reflash_BlockData, SynalockImgData, SynaFirmwareBlockSize);

			/*                         */
			SynalockImgData += SynaFirmwareBlockSize;

			/*                                    */
			cmd = m_uF34ReflashCmd_LockDown;
			writeRMI(ts->client, SynaF34_FlashControl, (unsigned char*)&cmd, 1);

			/*                                                                             */
			SynaWaitForATTN(1000,ts);
			CheckFlashStatus(ts,cmd);
		}

		//                                                     
		//                                                                            
		//                                                                                  
		SynaEnableFlashing(ts);
	}
	else TOUCH_ERR_MSG("Device already locked.\n");
}

//                                                                                                            
bool CheckTouchControllerType(struct synaptics_ts_data *ts)
{
	int ID;
	char buffer[5] = {0};
	char controllerType[20] = {0};
	unsigned char uData[4] = {0};

	readRMI(ts->client, (SynaF01QueryBase + 22), &SynaF01Query43Length, 1); //  

	if ((SynaF01Query43Length & 0x0f) > 0)
	{
		readRMI(ts->client, (SynaF01QueryBase + 23), &uData[0], 1);
		if (uData[0] & 0x01)
		{
			readRMI(ts->client, (SynaF01QueryBase + 17), &uData[0], 2);

			ID = ((int)uData[0] | ((int)uData[1] << 8));

			if (strstr(controllerType, buffer) != 0) return true;
			return false;
		}
		else return false;
	}
	else return false;
}

/*                                                        
 
                         
                          
       
                                                                                    

                        
  
                          
   
                                
   
  

                                        
              
              
 */


/*                                                                                       
                                                                                         
                                                           
 */
void SynaScanPDT(struct synaptics_ts_data *ts) //                
{
	unsigned char address;
	unsigned char uData[2] = {0}; //      
	unsigned char buffer[6] = {0};

	for (address = 0xe9; address > 0xc0; address = address - 6)
	{
		readRMI(ts->client, address, buffer, 6);

		if (!buffer[5])
			continue;
		switch (buffer[5])
		{
			case 0x34:
				SynaF34DataBase = buffer[3];
				SynaF34QueryBase = buffer[0];
				break;
			case 0x01:
				SynaF01DataBase = buffer[3];
				SynaF01CommandBase = buffer[1];
				SynaF01QueryBase = buffer[0];//      
				break;
		}
	}

	SynaF34Reflash_BlockNum = SynaF34DataBase;
	SynaF34Reflash_BlockData = SynaF34DataBase + 1; //  
	SynaF34ReflashQuery_BootID = SynaF34QueryBase;
	SynaF34ReflashQuery_FlashPropertyQuery = SynaF34QueryBase + 1;//  
	SynaF34ReflashQuery_BlockSize = SynaF34QueryBase + 2;//  
	SynaF34ReflashQuery_FirmwareBlockCount = SynaF34QueryBase + 3;//  
	SynaF34_FlashControl = SynaF34DataBase + 2;//                                                          
	SynaF34_FlashStatus = SynaF34DataBase + 3;//      

	readRMI(ts->client, SynaF34ReflashQuery_FirmwareBlockCount, buffer, 4);//                                                           
	SynaFirmwareBlockCount  = buffer[0] | (buffer[1] << 8);//      
	SynaConfigBlockCount    = buffer[2] | (buffer[3] << 8);

	readRMI(ts->client, SynaF34ReflashQuery_BlockSize, &uData[0], 2);
	SynaConfigBlockSize = SynaFirmwareBlockSize = uData[0] | (uData[1] << 8);

	//          
	readRMI(ts->client, (SynaF01DataBase + 1), buffer, 1);
}

/*                                           
*/
void SynaInitialize(struct synaptics_ts_data *ts)
{
	u8 data;

	TOUCH_INFO_MSG("\nInitializing Reflash Process...\n");


	data = 0x00;
	writeRMI(ts->client, 0xff, &data, 1);

	SynaImageParser(ts); //      

	SynaScanPDT(ts);	//            
}

/*                                                                                          
                                                       
 */
void SynaReadFirmwareInfo(struct synaptics_ts_data *ts)
{
	unsigned char uData[3] = {0};
	unsigned char product_id[11];
	int firmware_version;

	TOUCH_INFO_MSG("%s", __FUNCTION__);


	readRMI(ts->client, SynaF01QueryBase + 11, product_id, 10);
	product_id[10] = '\0';
	TOUCH_ERR_MSG("Read Product ID %s\n", product_id);

	readRMI(ts->client, SynaF01QueryBase + 18, uData, 3);
	firmware_version = uData[2] << 16 | uData[1] << 8 | uData[0];
	TOUCH_ERR_MSG("Read Firmware Info %d\n", firmware_version);

	CheckTouchControllerType(ts);
	/*                          */
}
//                             
/*                                                                                                 
*/
void SynaReadBootloadID(struct synaptics_ts_data *ts)
{
	unsigned char uData[2] = {0};

	readRMI(ts->client, SynaF34ReflashQuery_BootID, &uData[0], 2);
	SynaBootloadID = uData[0] | (uData[1] << 8);
	TOUCH_ERR_MSG("SynaBootloadID = %d\n", SynaBootloadID);
}

/*                                                                                                    
*/
void SynaWriteBootloadID(struct synaptics_ts_data *ts)
{
	unsigned char uData[2];

	uData[0] = SynaBootloadID % 0x100;
	uData[1] = SynaBootloadID / 0x100;

	TOUCH_ERR_MSG("uData[0] = %x uData[0] = %x\n", uData[0], uData[1]);
	writeRMI(ts->client, SynaF34Reflash_BlockData, &uData[0], 2);
}

/*                                                 
*/
void SynaEnableFlashing(struct synaptics_ts_data *ts)
{
	//            
	unsigned char uStatus = 0;
	enum FlashCommand cmd;
	unsigned char uData[3] = {0};
	int firmware_version;

	TOUCH_INFO_MSG("%s", __FUNCTION__);

	TOUCH_INFO_MSG("\nEnable Reflash...");
	readRMI (ts->client, SynaF01DataBase, &uStatus, 1);

	if ((uStatus &0x40) == 0)
	{
		//                                                                                          
		SynaReadBootloadID(ts);
		SynaWriteBootloadID(ts);

		//                                                                    
		//                                       
		cmd = m_uF34ReflashCmd_Enable;
		writeRMI(ts->client, SynaF34_FlashControl, (unsigned char*)&cmd, 1);
		SynaWaitForATTN(1000,ts);

		//                     
		//                      

		//                                                              
		SynaScanPDT(ts);

		readRMI(ts->client, SynaF01QueryBase + 18, uData, 3);
			firmware_version = uData[2] << 16 | uData[1] << 8 | uData[0];
				TOUCH_ERR_MSG("fw_reflash_twice? =	%d\n", ts->fw_info.fw_reflash_twice);
			if (firmware_version <= 1245782){
				ts->fw_info.fw_reflash_twice = 1;
				TOUCH_ERR_MSG("fw_reflash_twice =  %d\n", ts->fw_info.fw_reflash_twice);
				}

		//                                                                                    
		//            
		CheckFlashStatus(ts, cmd);
	}
}

/*                                                                               
*/
unsigned int SynaWaitForATTN(int timeout,struct synaptics_ts_data *ts)
{
	unsigned char uStatus;
	//                  
	//                             
	//              

	int trial_us=0;
#ifdef POLLING
	do {
		uStatus = 0x00;
		readRMI(ts->client, (SynaF01DataBase + 1), &uStatus, 1);
		if (uStatus != 0)
			break;
		Sleep(duration);
		times++;
	} while (times < retry);

	if (times == retry)
		return -1;
#else
	/*                                                    
  
            
  */
	while ((gpio_get_value(ts->pdata->int_pin) != 0) && (trial_us < (timeout * 1000))) {
		udelay(1);
		trial_us++;
	}
	if (gpio_get_value(ts->pdata->int_pin) != 0) {
		TOUCH_ERR_MSG("interrupt pin is busy...");
		return -1;
	}

	readRMI(ts->client, (SynaF01DataBase + 1), &uStatus, 1);
#endif
	return 0;
}
/*                                                  
*/
void SynaFinalizeReflash(struct synaptics_ts_data *ts)
{
	unsigned char uData;

	char deviceStatusStr[7][20] = {
		"0x00",
		"0x01",
		"0x02",
		"0x03",
		"config CRC failed",
		"firmware CRC failed",
		"CRC in progress\n"
	};

	TOUCH_INFO_MSG("%s", __FUNCTION__);

	TOUCH_INFO_MSG("\nFinalizing Reflash...");

	//                                                                    
	//                                                                             
	uData = 1;
	writeRMI(ts->client, SynaF01CommandBase, &uData, 1);

	//                                                              
	//                                            
	msleep(150);
	SynaWaitForATTN(1000,ts);

	SynaScanPDT(ts);

	readRMI(ts->client, SynaF01DataBase, &uData, 1);

	if ((uData & 0x40) != 0)
	{
		TOUCH_ERR_MSG("\nDevice is in bootloader mode (status: %s).\n", deviceStatusStr[uData & 0xF]);
		ts->fw_info.fw_reflash_twice = 1;
	}
	else
	{
		TOUCH_ERR_MSG("\nReflash Completed and Succeed.\n");
	}
}

/*                                                                               
*/
void SynaFlashFirmwareWrite(struct synaptics_ts_data *ts)
{
	//                                                                      
	unsigned char *puFirmwareData = SynafirmwareImgData;
	unsigned char uData[2];
	unsigned short blockNum;
	enum FlashCommand cmd;

	for (blockNum = 0; blockNum < SynaFirmwareBlockCount; ++blockNum)
	{
		if (blockNum == 0)
		{

			//                                                                                       
			uData[0] = blockNum & 0xff;
			uData[1] = (blockNum & 0xff00) >> 8;
			writeRMI(ts->client, SynaF34Reflash_BlockNum, &uData[0], 2);
		}

		writeRMI(ts->client, SynaF34Reflash_BlockData, puFirmwareData, SynaFirmwareBlockSize);
		puFirmwareData += SynaFirmwareBlockSize;

		//                                         
		cmd = m_uF34ReflashCmd_FirmwareWrite;
		writeRMI(ts->client, SynaF34_FlashControl, (unsigned char*)&cmd, 1);

		//                         
		CheckFlashStatus(ts, cmd);
		//                                                                                                                    
#ifdef SHOW_PROGRESS
		if (blockNum % 100 == 0)
			TOUCH_ERR_MSG("blk %d / %d\n", blockNum, SynaFirmwareBlockCount);
#endif
	}
#ifdef SHOW_PROGRESS
	TOUCH_ERR_MSG("blk %d / %d\n", SynaFirmwareBlockCount, SynaFirmwareBlockCount);
#endif
}

/*                                                                               
*/
void SynaFlashConfigWrite(struct synaptics_ts_data *ts)
{
	//                                                                    
	unsigned char *puConfigData = SynaconfigImgData;
	unsigned char uData[2];
	unsigned short blockNum;
	enum FlashCommand cmd;

	for (blockNum = 0; blockNum < SynaConfigBlockCount; ++blockNum)
	{
		//                                                                                       
		uData[0] = blockNum & 0xff;
		uData[1] = (blockNum & 0xff00) >> 8;
		writeRMI(ts->client, SynaF34Reflash_BlockNum, &uData[0], 2);

		writeRMI(ts->client, SynaF34Reflash_BlockData, puConfigData, SynaConfigBlockSize);
		puConfigData += SynaConfigBlockSize;

		//                                       
		cmd = m_uF34ReflashCmd_ConfigWrite;
		writeRMI(ts->client, SynaF34_FlashControl, (unsigned char*)&cmd, 1);

		SynaWaitForATTN(100,ts);
		CheckFlashStatus(ts, cmd);
#ifdef SHOW_PROGRESS
		if (blockNum % 100 == 0)
			TOUCH_ERR_MSG("blk %d / %d\n", blockNum, SynaConfigBlockCount);
#endif
	}
#ifdef SHOW_PROGRESS
	TOUCH_ERR_MSG("blk %d / %d\n", SynaConfigBlockCount, SynaConfigBlockCount);
#endif
}


/*                                         
*/
void eraseAllBlock(struct synaptics_ts_data *ts)
{
	enum FlashCommand cmd;

	//                                                                     
	SynaReadBootloadID(ts);
	SynaWriteBootloadID(ts);

	//                                
	cmd = m_uF34ReflashCmd_EraseAll;
	writeRMI(ts->client, SynaF34_FlashControl, (unsigned char*)&cmd, 1);

	SynaWaitForATTN(6000,ts);
	CheckFlashStatus(ts, cmd);
}

/*                                                          
*/
void SynaProgramFirmware(struct synaptics_ts_data *ts)
{
	TOUCH_ERR_MSG("\nProgram Firmware Section...\n");

	eraseAllBlock(ts);

	SynaFlashFirmwareWrite(ts);

	SynaFlashConfigWrite(ts);
}

/*                                                          
*/
void SynaUpdateConfig(struct synaptics_ts_data *ts)
{
	TOUCH_ERR_MSG("\nUpdate Config Section...\n");

	EraseConfigBlock(ts);

	SynaFlashConfigWrite(ts);
}



/*                                         
*/
void EraseConfigBlock(struct synaptics_ts_data *ts)
{
	enum FlashCommand cmd;

	//                                                                     
	SynaReadBootloadID(ts);
	SynaWriteBootloadID(ts);

	//                                
	cmd = m_uF34ReflashCmd_EraseUIConfig;
	writeRMI(ts->client, SynaF34_FlashControl, (unsigned char*)&cmd, 1);

	SynaWaitForATTN(2000,ts);
	CheckFlashStatus(ts, cmd);
}


/*                                                                                                
*/
void CompleteReflash(struct synaptics_ts_data *ts)
{
	bool bFlashAll = true;

	SynaInitialize(ts);

	SynaReadFirmwareInfo(ts);

	SynaEnableFlashing(ts);

	SynaBootloaderLock(ts);

	if (bFlashAll)
		SynaProgramFirmware(ts);
	else
		SynaUpdateConfig(ts);

	SynaFinalizeReflash(ts);
}
