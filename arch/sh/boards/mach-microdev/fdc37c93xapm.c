/*
 *
 * Setup for the SMSC FDC37C93xAPM
 *
 * Copyright (C) 2003 Sean McGoogan (Sean.McGoogan@superh.com)
 * Copyright (C) 2003, 2004 SuperH, Inc.
 * Copyright (C) 2004, 2005 Paul Mundt
 *
 * SuperH SH4-202 MicroDev board support.
 *
 * May be copied or modified under the terms of the GNU General Public
 * License.  See linux/COPYING for more information.
 */
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/err.h>
#include <mach/microdev.h>

#define SMSC_CONFIG_PORT_ADDR	 (0x3F0)
#define SMSC_INDEX_PORT_ADDR	 SMSC_CONFIG_PORT_ADDR
#define SMSC_DATA_PORT_ADDR	 (SMSC_INDEX_PORT_ADDR + 1)

#define SMSC_ENTER_CONFIG_KEY	 0x55
#define SMSC_EXIT_CONFIG_KEY	 0xaa

#define SMCS_LOGICAL_DEV_INDEX	 0x07	/*                       */
#define SMSC_DEVICE_ID_INDEX	 0x20	/*           */
#define SMSC_DEVICE_REV_INDEX	 0x21	/*                 */
#define SMSC_ACTIVATE_INDEX	 0x30	/*          */
#define SMSC_PRIMARY_BASE_INDEX	 0x60	/*                      */
#define SMSC_SECONDARY_BASE_INDEX 0x62	/*                        */
#define SMSC_PRIMARY_INT_INDEX	 0x70	/*                          */
#define SMSC_SECONDARY_INT_INDEX 0x72	/*                            */
#define SMSC_HDCS0_INDEX	 0xf0	/*                       */
#define SMSC_HDCS1_INDEX	 0xf1	/*                       */

#define SMSC_IDE1_DEVICE	1	/*                       */
#define SMSC_IDE2_DEVICE	2	/*                       */
#define SMSC_PARALLEL_DEVICE	3	/*                              */
#define SMSC_SERIAL1_DEVICE	4	/*                          */
#define SMSC_SERIAL2_DEVICE	5	/*                          */
#define SMSC_KEYBOARD_DEVICE	7	/*                         */
#define SMSC_CONFIG_REGISTERS	8	/*                                   */

#define SMSC_READ_INDEXED(index) ({ \
	outb((index), SMSC_INDEX_PORT_ADDR); \
	inb(SMSC_DATA_PORT_ADDR); })
#define SMSC_WRITE_INDEXED(val, index) ({ \
	outb((index), SMSC_INDEX_PORT_ADDR); \
	outb((val),   SMSC_DATA_PORT_ADDR); })

#define	IDE1_PRIMARY_BASE	0x01f0	/*                                   */
#define	IDE1_SECONDARY_BASE	0x03f6	/*                                       */
#define	IDE2_PRIMARY_BASE	0x0170	/*                                   */
#define	IDE2_SECONDARY_BASE	0x0376	/*                                       */

#define SERIAL1_PRIMARY_BASE	0x03f8
#define SERIAL2_PRIMARY_BASE	0x02f8

#define	MSB(x)		( (x) >> 8 )
#define	LSB(x)		( (x) & 0xff )

	/*                                                */
#define	MICRODEV_FPGA_GP_BASE		0xa6100000ul

static int __init smsc_superio_setup(void)
{

	unsigned char devid, devrev;

		/*                                    */
		/*                                 */
	outb(SMSC_ENTER_CONFIG_KEY, SMSC_CONFIG_PORT_ADDR);

		/*                     */
	devid  = SMSC_READ_INDEXED(SMSC_DEVICE_ID_INDEX);
	devrev = SMSC_READ_INDEXED(SMSC_DEVICE_REV_INDEX);

	if ((devid == 0x30) && (devrev == 0x01))
		printk("SMSC FDC37C93xAPM SuperIO device detected\n");
	else
		return -ENODEV;

		/*                            */
	SMSC_WRITE_INDEXED(SMSC_KEYBOARD_DEVICE, SMCS_LOGICAL_DEV_INDEX);
		/*           */
	SMSC_WRITE_INDEXED(1, SMSC_ACTIVATE_INDEX);
		/*                       */
	SMSC_WRITE_INDEXED(MICRODEV_FPGA_IRQ_KEYBOARD, SMSC_PRIMARY_INT_INDEX);
	SMSC_WRITE_INDEXED(MICRODEV_FPGA_IRQ_MOUSE, SMSC_SECONDARY_INT_INDEX);

		/*                             */
	SMSC_WRITE_INDEXED(SMSC_SERIAL1_DEVICE, SMCS_LOGICAL_DEV_INDEX);
		/*           */
	SMSC_WRITE_INDEXED(1, SMSC_ACTIVATE_INDEX);
		/*                             */
	SMSC_WRITE_INDEXED(MSB(SERIAL1_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+0);
	SMSC_WRITE_INDEXED(LSB(SERIAL1_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+1);
	SMSC_WRITE_INDEXED(0x00, SMSC_HDCS0_INDEX);
		/*                       */
	SMSC_WRITE_INDEXED(MICRODEV_FPGA_IRQ_SERIAL1, SMSC_PRIMARY_INT_INDEX);

		/*                             */
	SMSC_WRITE_INDEXED(SMSC_SERIAL2_DEVICE, SMCS_LOGICAL_DEV_INDEX);
		/*           */
	SMSC_WRITE_INDEXED(1, SMSC_ACTIVATE_INDEX);
		/*                             */
	SMSC_WRITE_INDEXED(MSB(SERIAL2_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+0);
	SMSC_WRITE_INDEXED(LSB(SERIAL2_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+1);
	SMSC_WRITE_INDEXED(0x00, SMSC_HDCS0_INDEX);
		/*                       */
	SMSC_WRITE_INDEXED(MICRODEV_FPGA_IRQ_SERIAL2, SMSC_PRIMARY_INT_INDEX);

		/*                         */
	SMSC_WRITE_INDEXED(SMSC_IDE1_DEVICE, SMCS_LOGICAL_DEV_INDEX);
		/*           */
	SMSC_WRITE_INDEXED(1, SMSC_ACTIVATE_INDEX);
		/*                             */
	SMSC_WRITE_INDEXED(MSB(IDE1_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+0);
	SMSC_WRITE_INDEXED(LSB(IDE1_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+1);
	SMSC_WRITE_INDEXED(MSB(IDE1_SECONDARY_BASE), SMSC_SECONDARY_BASE_INDEX+0);
	SMSC_WRITE_INDEXED(LSB(IDE1_SECONDARY_BASE), SMSC_SECONDARY_BASE_INDEX+1);
	SMSC_WRITE_INDEXED(0x0c, SMSC_HDCS0_INDEX);
	SMSC_WRITE_INDEXED(0x00, SMSC_HDCS1_INDEX);
		/*                      */
	SMSC_WRITE_INDEXED(MICRODEV_FPGA_IRQ_IDE1, SMSC_PRIMARY_INT_INDEX);

		/*                         */
	SMSC_WRITE_INDEXED(SMSC_IDE2_DEVICE, SMCS_LOGICAL_DEV_INDEX);
		/*           */
	SMSC_WRITE_INDEXED(1, SMSC_ACTIVATE_INDEX);
		/*                             */
	SMSC_WRITE_INDEXED(MSB(IDE2_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+0);
	SMSC_WRITE_INDEXED(LSB(IDE2_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+1);
	SMSC_WRITE_INDEXED(MSB(IDE2_SECONDARY_BASE), SMSC_SECONDARY_BASE_INDEX+0);
	SMSC_WRITE_INDEXED(LSB(IDE2_SECONDARY_BASE), SMSC_SECONDARY_BASE_INDEX+1);
		/*                      */
	SMSC_WRITE_INDEXED(MICRODEV_FPGA_IRQ_IDE2, SMSC_PRIMARY_INT_INDEX);

		/*                                    */
	SMSC_WRITE_INDEXED(SMSC_CONFIG_REGISTERS, SMCS_LOGICAL_DEV_INDEX);
		/*                                                        
                                          
                                               
                                                               
                                                                     
   */
	SMSC_WRITE_INDEXED(0x00, 0xc2);	/*                 */
	SMSC_WRITE_INDEXED(0x01, 0xc5);	/*                 */
	SMSC_WRITE_INDEXED(0x00, 0xc6);	/*               */
	SMSC_WRITE_INDEXED(0x00, 0xc7);	/*               */
	SMSC_WRITE_INDEXED(0x08, 0xe8);	/*                 */

		/*                              */
	outb(SMSC_EXIT_CONFIG_KEY, SMSC_CONFIG_PORT_ADDR);

	return 0;
}
device_initcall(smsc_superio_setup);
