/****************************************************************************
 *   FileName    : tcc353x_rf.c
 *   Description : TCC353X RF control functions
 ****************************************************************************
 *
 *   TCC Version 1.0
 *   Copyright (c) Telechips Inc.
 *   All rights reserved 
 
This source code contains confidential information of Telechips.
Any unauthorized use without a written permission of Telechips including not limited to re-
distribution in source or binary form is strictly prohibited.
This source code is provided "AS IS" and nothing contained in this source code shall 
constitute any express or implied warranty of any kind, including without limitation, any warranty 
of merchantability, fitness for a particular purpose or non-infringement of any patent, copyright 
or other third party intellectual property right. No warranty is made, express or implied, 
regarding the information's accuracy, completeness, or performance. 
In no event shall Telechips be liable for any claim, damages or other liability arising from, out of 
or in connection with this source code or the use in the source code. 
This source code is provided subject to the terms of a Mutual Non-Disclosure Agreement 
between Telechips and Company.
*
****************************************************************************/

#include "tcc353x_rf.h"
#include "tcc353x_command_control.h"
#include "tcc353x_register_control.h"
#include "tcpal_os.h"

/*                 */
I64U Tcc353xDiv64(I64U x, I64U y);

#define SCALE       22
#define FIXED(x)    (x<<SCALE)
#define MUL(A,B)    ((A*B)>>SCALE)
#define DIV(A,B)    (Tcc353xDiv64((A<<SCALE), B))

#ifndef Bit0
#define Bit31       0x80000000
#define Bit30       0x40000000
#define Bit29       0x20000000
#define Bit28       0x10000000
#define Bit27       0x08000000
#define Bit26       0x04000000
#define Bit25       0x02000000
#define Bit24       0x01000000
#define Bit23       0x00800000
#define Bit22       0x00400000
#define Bit21       0x00200000
#define Bit20       0x00100000
#define Bit19       0x00080000
#define Bit18       0x00040000
#define Bit17       0x00020000
#define Bit16       0x00010000
#define Bit15       0x00008000
#define Bit14       0x00004000
#define Bit13       0x00002000
#define Bit12       0x00001000
#define Bit11       0x00000800
#define Bit10       0x00000400
#define Bit9        0x00000200
#define Bit8        0x00000100
#define Bit7        0x00000080
#define Bit6        0x00000040
#define Bit5        0x00000020
#define Bit4        0x00000010
#define Bit3        0x00000008
#define Bit2        0x00000004
#define Bit1        0x00000002
#define Bit0        0x00000001
#define BitNONE     0x00000000
#endif

#ifndef BITSET
#define BITSET(X, MASK)             ( (X) |= (I32U)(MASK) )
#endif
#ifndef BITCLR
#define BITCLR(X, MASK)             ( (X) &= ~((I32U)(MASK)) )
#endif

#define _RFREG_CNT_	0x10
#define _RFREG_FORM_	5

extern Tcc353xHandle_t Tcc353xHandle[TCC353X_MAX][TCC353X_DIVERSITY_MAX];
I32U Tcc353xRfRegSRVersion[_RFREG_CNT_][_RFREG_FORM_] = {
	/*                                                                         */
	{0x00, 0, 0x35300000, 0x35300000, 0x35300000},
	{0x01, 1, 0x80000000, 0x80000000, 0x80000000},
	{0x02, 0, 0x00020000, 0x00020000, 0x00020000},
	{0x03, 0, 0x00000000, 0x00000000, 0x00000000},
	{0x04, 1, 0x00020003, 0x00020005, 0x00020006},
	{0x05, 1, 0x5435343D, 0x5435343D, 0x5435343D},
	{0x06, 1, 0x55555555, 0x55555555, 0x55555555},
	{0x07, 1, 0x64202F15, 0x64202F13, 0x64202F11},
	{0x08, 1, 0x80000000, 0x80000000, 0x80000000},
	{0x09, 1, 0x00868939, 0x00864989, 0x00768989},
	{0x0A, 1, 0x13773300, 0x13773300, 0x09772900},
	{0x0B, 1, 0x961B0D04, 0x961B0D04, 0x961B0D04},
	{0x0C, 1, 0x040404E0, 0x040404E0, 0x040404E0},
	{0x0D, 1, 0x021DDFFD, 0x021DDFFD, 0x021DDFFD},
	{0x0E, 1, 0x7F603048, 0x7F602860, 0x7F043060},
	{0x0F, 1, 0x0000007F, 0x0000007F, 0x0000007F} 
};

I32S Tcc353xRfBandIndex[TCC353X_MAX][TCC353X_DIVERSITY_MAX];

static I32S Tcc353xRfBandChange(I32S _moduleIndex, I32S _diversityIndex, 
				I32S _bandIndex)
{
	I32U i = 0;
	I32U tcc353xRfReg[_RFREG_CNT_][_RFREG_FORM_];
	I08U addressArray[0x10];
	I32U dataArray[0x10];
	I32U arraySize = 0;

	if (_bandIndex != _IDX_FM_ &&  _bandIndex != _IDX_VHF_ 
	    && _bandIndex != _IDX_UHF_)
	{
		Tcc353xRfBandIndex[_moduleIndex][_diversityIndex] = -1;
		return TCC353X_RETURN_FAIL;
	}

	/*                      */
	/*               */
	if (_bandIndex == Tcc353xRfBandIndex[_moduleIndex][_diversityIndex])
		return TCC353X_RETURN_SUCCESS;

	Tcc353xRfBandIndex[_moduleIndex][_diversityIndex] = _bandIndex;

	TcpalMemcpy(&tcc353xRfReg, &Tcc353xRfRegSRVersion,
		    sizeof(tcc353xRfReg));

	for (i = 0; i < _RFREG_CNT_; i++) {
		if (tcc353xRfReg[i][_IDX_ACCESSABLE_])
		{
			addressArray[arraySize] = (I08U)(i);
			dataArray[arraySize] = tcc353xRfReg[i][_bandIndex];
			arraySize++;
		}
	}

	Tcc353xRfWriteEx(_moduleIndex, _diversityIndex, &addressArray[0], 
			 &dataArray[0], arraySize);

	if(_bandIndex == _IDX_FM_)
		TcpalPrintLog((I08S *) "[TCC353X] Band Switch to FM\n");
	else if(_bandIndex == _IDX_VHF_)
		TcpalPrintLog((I08S *) "[TCC353X] Band Switch to VHF\n");
	else
		TcpalPrintLog((I08S *) "[TCC353X] Band Switch to UHF\n");
	return TCC353X_RETURN_SUCCESS;
}

I32S Tcc353xRfInit(I32S _moduleIndex, I32S _diversityIndex)
{
	I32U RfId = 0x00;

	/*                     */
	Tcc353xRfBandIndex[_moduleIndex][_diversityIndex] = -1;

	Tcc353xRfRead(_moduleIndex, _diversityIndex, 0x00, &RfId);
	if (RfId != 0x35300000) {
		TcpalPrintErr((I08S *)
			      "[TCC353X] RF ID Read Error [%d][%d][0x%x]\n",
			      _moduleIndex, _diversityIndex, RfId);
		return TCC353X_RETURN_FAIL;
	} else {
		TcpalPrintLog((I08S *) 
			      "[TCC353X] RF ID Read OK.[%d][%d][0x%x]\n",
			      _moduleIndex, _diversityIndex, RfId);
	}

	/*                     */
	Tcc353xRfBandChange(_moduleIndex, _diversityIndex, _IDX_UHF_);
	return TCC353X_RETURN_SUCCESS;
}

static I32U Tcc353xRfGetBandIndex(Tcc353xHandle_t *_handle, I32S _freq_khz)
{
	I32U maxFmFreq = 138000;
	I32U maxVhfFreq = 276000;
	I32U bandIdx = _IDX_UHF_;

	if(_handle->options.basebandName == BB_TCC3535) {
		/*         */
		maxFmFreq = 150000;
		maxVhfFreq = 423000;
	} else {
		/*                         */
		if(_handle->options.rfType == TCC353X_TRIPLE_BAND_RF) {
			maxFmFreq = 249000;
			maxVhfFreq = 423000;
		} else {
			maxFmFreq = 0;
			maxVhfFreq = 276000;
		}
	}
	
	if ((I32U)(_freq_khz) < maxFmFreq)		/*    */
		bandIdx = _IDX_FM_;
	else if ((I32U)(_freq_khz) < maxVhfFreq)	/*     */
		bandIdx = _IDX_VHF_;
	else						/*     */
		bandIdx = _IDX_UHF_;

	return bandIdx;
}

/*                            */
void Tcc353xRfSwitching(I32S _moduleIndex, I32S _diversityIndex,
		        I32S _frequency, Tcc353xOption_t * _option)
{
	I08U gpioLRoriginal = 0x00;
	I08U gpioDRoriginal = 0x00;
	I08U i = 0x00;
	I08U switchingGpioValue = 0x00;
	I08U valueVhfL = 0x00;
	I08U valueVhfH = 0x00;
	I08U valueUhf = 0x00;
	/*                           */
	I32U bandIndex;

	bandIndex = Tcc353xRfGetBandIndex(&Tcc353xHandle[_moduleIndex][0], 
					  _frequency);
	for(i=0; i<3; i++)
	{
		switchingGpioValue = 
		    (I08U)((Tcc353xHandle[_moduleIndex][_diversityIndex].
		    options.rfSwitchingGpioN>>(i*8)) & 0xFF);
		valueVhfL = 
		    (I08U)((Tcc353xHandle[_moduleIndex][_diversityIndex].
		    options.rfSwitchingVhfLow>>(i*8)) & 0xFF);
		valueVhfH = 
		    (I08U)((Tcc353xHandle[_moduleIndex][_diversityIndex].
		    options.rfSwitchingVhfHigh>>(i*8)) & 0xFF);
		valueUhf = 
		    (I08U)((Tcc353xHandle[_moduleIndex][_diversityIndex].
		    options.rfSwitchingUhf>>(i*8)) & 0xFF);
		
		if(switchingGpioValue != 0x00) {
			Tcc353xSetRegIoCfgMux(&Tcc353xHandle[_moduleIndex]
					      [_diversityIndex], i);
			
			Tcc353xGetRegGpioDR(&Tcc353xHandle[_moduleIndex]
					    [_diversityIndex], &gpioDRoriginal);
			
			Tcc353xGetRegGpioLR(&Tcc353xHandle[_moduleIndex]
					    [_diversityIndex], &gpioLRoriginal);

			BITSET(gpioDRoriginal, switchingGpioValue);
			BITCLR(gpioLRoriginal, switchingGpioValue);

			switch(bandIndex) {
			case _IDX_FM_:
				BITSET(gpioLRoriginal, valueVhfL);	/*         */
			break;
			case _IDX_VHF_:
				BITSET(gpioLRoriginal, valueVhfH);	/*          */
			break;
			case _IDX_UHF_:
				BITSET(gpioLRoriginal, valueUhf);	/*     */
			break;
			default:
				BITSET(gpioLRoriginal, valueUhf);	/*     */
			break;
			}
			
			Tcc353xSetRegGpioDR(&Tcc353xHandle[_moduleIndex]
					    [_diversityIndex], gpioDRoriginal);
			Tcc353xSetRegGpioLR(&Tcc353xHandle[_moduleIndex]
					    [_diversityIndex], gpioLRoriginal);

		}		
	}
}

static I32U Tcc353xRfGetMatchingIndex (I32S _freq_khz, I32S *_table)
{
	I32U i;
	
	for(i=0; i<8; i++) {
		if((_freq_khz >= _table[i]) && (_table[i] >= 0))
			return i;
	}

	return 7;	/*         */
}

static I32U Tcc353xRfGetMatchingReg (Tcc353xHandle_t *_handle, 
				     I32S _freq_khz,
				     Tcc353xTuneOptions * _tuneOption, 
				     I32U _bandIdx)
{
	/*               */
	I32U reg = 0x00868989;
	I32U matchingCtrlBit = 0;
	I32U tableIndex = 0;

	/*                            */
	/*                                                                                 */

        I32S tcc353xMatching_DualBand[3][8] = {
                {    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1},
                {    -1,    -1,    -1,207143,191143,185143,     0,     0},
                {773143,737143,683143,623143,563143,527143,497143,     0}
        };
        
        I32S tcc353xMatching_TripleBand[3][8] = {
                {207143,179143,167143,153143,135143,123143,111143, 93143},
                {381143,351143,333143,309143,297143,279143,267143,249143},
                {731143,707143,671143,641143,599143,569143,533143,423143}
        };

        I32S tcc3535Matching[3][8] = {
		{ 94000, 83000, 70000, 64000, 60000, 55000,	0,     0},
		{207143,191143,185143,173143,	  0,	 0,	0,     0},
		{671143,533143,503143,485143,473143,	 0,	0,     0}
        };

	/*                          */
	if(_tuneOption->segmentType == TCC353X_ISDBTMM) {
		reg = 0x00861989;
		return reg;
	}

	switch (_bandIdx) {
	case _IDX_FM_:
		BITCLR(reg, 0xF0);
		BITSET(reg, 0x808000);
		tableIndex = 0;
		break;
	case _IDX_VHF_:
		BITCLR(reg, 0xF000);
		BITSET(reg, 0x800080);
		tableIndex = 1;
		break;
	case _IDX_UHF_:
		BITCLR(reg, 0xF00000);
		BITSET(reg, 0x008080);
		tableIndex = 2;
		break;
	default:	/*     */
		BITCLR(reg, 0xF00000);
		BITSET(reg, 0x008080);
		tableIndex = 2;
		break;
	}

	if(_handle->options.basebandName == BB_TCC3535) {
		matchingCtrlBit = Tcc353xRfGetMatchingIndex (
		    _freq_khz, &tcc3535Matching[tableIndex][0]);
	} else {
		if(_handle->options.rfType == TCC353X_TRIPLE_BAND_RF)
			matchingCtrlBit = Tcc353xRfGetMatchingIndex (
			    _freq_khz, 
			    &tcc353xMatching_TripleBand[tableIndex][0]);
		else 
			matchingCtrlBit = Tcc353xRfGetMatchingIndex (
			    _freq_khz, 
			    &tcc353xMatching_DualBand[tableIndex][0]);
	}

	switch (_bandIdx) {
	case _IDX_FM_:
		BITSET(reg, (matchingCtrlBit<<4));
		break;
	case _IDX_VHF_:
		BITSET(reg, (matchingCtrlBit<<12));
		break;
	case _IDX_UHF_:
		BITSET(reg, (matchingCtrlBit<<20));
		break;
	default:	/*     */
		BITSET(reg, (matchingCtrlBit<<20));
		break;
	}

	return reg;
}

void Tcc353xRfTune(I32S _moduleIndex, I32S _diversityIndex, I32S _freq_khz,
		   I32S _bw_khz, I32S _oscClk,
		   Tcc353xTuneOptions * _tuneOption)
{
	I64U N, F;
	I64U Flo, VCO_DIV, FOffset, Fvco, FR;
	I64U N_int, intF;
	I64U fXtal, fpfd, f_freq_khz;
	I32U OSCCLK;
	I08U RCNT_RDC = 0;
	I08U REG_VCO_DIV;
	I32U Icp;
	/*                      */
	I08U i;
	I32U rfReg[0x10];
	/*                         */
	I32U bandIdx;
	I64U pllMode = 2;
	I32U tcc353xRfReg[_RFREG_CNT_][_RFREG_FORM_];
	I08U addressArray[0x10];
	I32U dataArray[0x10];
	I32U arraySize = 0;
	I32U use_lowif = 0;
	I32U use_seg = 13;

	TcpalMemcpy(&tcc353xRfReg, &Tcc353xRfRegSRVersion,
		    sizeof(tcc353xRfReg));

	/*                */
	bandIdx = Tcc353xRfGetBandIndex(
	    &Tcc353xHandle[_moduleIndex][_diversityIndex], _freq_khz); 

	Tcc353xRfBandChange(_moduleIndex, _diversityIndex, bandIdx);

	/*                 */
	for (i = 0; i < _RFREG_CNT_; i++)
		rfReg[i] = tcc353xRfReg[i][bandIdx];

	switch (_tuneOption->segmentType) {
	case TCC353X_ISDBT_1_OF_13SEG:
		if (_tuneOption->rfIfType != TCC353X_ZERO_IF)
			_freq_khz += 1000;
		/*                */
		break;
	case TCC353X_ISDBTSB_1SEG:
	case TCC353X_ISDBTSB_1_OF_3SEG:
		if (_tuneOption->rfIfType != TCC353X_ZERO_IF)
			_freq_khz += 1000;
		break;
	case TCC353X_ISDBTSB_3SEG:
		if (_tuneOption->rfIfType != TCC353X_ZERO_IF)
			_freq_khz += 1000;
		/*                */
		break;
	case TCC353X_ISDBT_13SEG:
		/*                 */
		break;
	case TCC353X_ISDBTMM:
		/*          */
		if (_tuneOption->rfIfType != TCC353X_ZERO_IF) {
			if(_tuneOption->tmmSet != A_1st_13Seg &&
			_tuneOption->tmmSet != A_2nd_13Seg &&
			_tuneOption->tmmSet != B_1st_13Seg &&
			_tuneOption->tmmSet != B_2nd_13Seg &&
			_tuneOption->tmmSet != C_1st_13Seg &&
			_tuneOption->tmmSet != C_2nd_13Seg &&
			_tuneOption->tmmSet != UserDefine_Tmm13Seg)
			/*                                  */
				_freq_khz += 1000;
		}
		break;
	default:
		/*                      */
		/*                 */
		break;
	}

	OSCCLK = _oscClk;
	fXtal = OSCCLK;
	f_freq_khz = _freq_khz;

	/*               */
	if (f_freq_khz < 65000) {
		VCO_DIV = 48;
		REG_VCO_DIV = 0x07;
		pllMode = 2;
	}

	else if (f_freq_khz < 90000) {
		VCO_DIV = 32;
		REG_VCO_DIV = 0x06;
		pllMode = 2;
	}

	else if (f_freq_khz < 138000) {
		VCO_DIV = 24;
		REG_VCO_DIV = 0x05;
		pllMode = 2;
	}

	else if (f_freq_khz < 182000) {
		VCO_DIV = 16;
		REG_VCO_DIV = 0x04;
		pllMode = 2;
	}

	else if (f_freq_khz < 276000) {
		VCO_DIV = 12;
		REG_VCO_DIV = 0x03;
		pllMode = 2;
	}

	else if (f_freq_khz < 366000) {
		VCO_DIV = 8;
		REG_VCO_DIV = 0x02;
		pllMode = 2;
	}

	else if (f_freq_khz < 580000) {
		VCO_DIV = 6;
		REG_VCO_DIV = 0x01;
		pllMode = 2;
	}

	else {
		VCO_DIV = 4;
		REG_VCO_DIV = 0x00;
		pllMode = 3;
	}

	FOffset = 0;
	FR = 1;
	/*                 */
	fpfd = DIV(fXtal, FR);
	fpfd = (fpfd >> SCALE);

	Flo = f_freq_khz - FOffset;
	Fvco = Flo * VCO_DIV;

	/*                            */
	N = DIV(Fvco, pllMode * fpfd);
	N_int = (N >> SCALE) << SCALE;

	/*                                                       */
	F = ((N - N_int) * (2 << 21)) >> SCALE;
	N_int = (N_int >> SCALE);

	intF = F;
	RCNT_RDC = (I08U) (FR);
	Icp = 4 << 24;

	/*                                    */
	BITCLR(tcc353xRfReg[0x05][bandIdx], 0x07000001);
	BITCLR(tcc353xRfReg[0x07][bandIdx], 0x0000007F);
	BITCLR(tcc353xRfReg[0x08][bandIdx], 0x3FFFFFFF);

	rfReg[0x05] = ((tcc353xRfReg[0x05][bandIdx] & 0xF8FFFFFF) | Icp);
	rfReg[0x07] = tcc353xRfReg[0x07][bandIdx] & 0xFFFFFF80;

	if (pllMode == 2)
		rfReg[0x07] |= RCNT_RDC << 4 | (REG_VCO_DIV & 0x07);
	else
		rfReg[0x07] |=
		    RCNT_RDC << 4 | 1 << 3 | (REG_VCO_DIV & 0x07);

	rfReg[0x08] =(I32U)
	    (tcc353xRfReg[0x08][bandIdx] | (N_int & 0xFF) |
	     ((intF & 0x3FFFFF) << 8));

	/*                  */
	if(bandIdx == _IDX_UHF_)	/*                      */
		rfReg[0x04] = ((rfReg[0x04] & 0xFFFFFFF8) | 0x06);
	else if(bandIdx == _IDX_VHF_)	/*                      */
		rfReg[0x04] = ((rfReg[0x04] & 0xFFFFFFF8) | 0x05);
	else				/*                       */
		rfReg[0x04] = ((rfReg[0x04] & 0xFFFFFFF8) | 0x03);

	switch (_tuneOption->segmentType) {
	case TCC353X_ISDBT_1_OF_13SEG:
	case TCC353X_ISDBTSB_1SEG:
	case TCC353X_ISDBTSB_1_OF_3SEG:
		use_seg = 1;
		if (_tuneOption->rfIfType == TCC353X_LOW_IF)
			use_lowif = 1;
		else
			use_lowif = 0;
		break;
	case TCC353X_ISDBTSB_3SEG:
		use_seg = 3;
		if (_tuneOption->rfIfType == TCC353X_LOW_IF)
			use_lowif = 1;
		else
			use_lowif = 0;
		break;
	case TCC353X_ISDBT_13SEG:
		use_seg = 13;
		use_lowif = 0;
		break;
	case TCC353X_ISDBTMM:
		if (_tuneOption->tmmSet == A_1st_13Seg ||
		    _tuneOption->tmmSet == A_2nd_13Seg ||
		    _tuneOption->tmmSet == B_1st_13Seg ||
		    _tuneOption->tmmSet == B_2nd_13Seg ||
		    _tuneOption->tmmSet == C_1st_13Seg ||
		    _tuneOption->tmmSet == C_2nd_13Seg ||
		    _tuneOption->tmmSet == UserDefine_Tmm13Seg) {
		    use_seg = 13;
		    use_lowif = 0;
		} else {
			use_seg = 1;
			if (_tuneOption->rfIfType == TCC353X_LOW_IF)
				use_lowif = 1;
			else
				use_lowif = 0;
		}
		break;
	default:
		break;
	}

	if(use_lowif)
		rfReg[0x04] = ((rfReg[0x04] & 0xFFFFF9FF) | 0x0200);
	else
		rfReg[0x04] = (rfReg[0x04] & 0xFFFFF9FF);

	/*                  */
	BITCLR(rfReg[0x0C], 0x3F00);
	if (use_seg==13)
		BITSET(rfReg[0x0C], 0x400);
	else if (use_seg==1)	/*             */
		BITSET(rfReg[0x0C], 0x200);
	else
		BITSET(rfReg[0x0C], 0x200);

	BITCLR(rfReg[0x0C], 0x000F4004);
	if(use_lowif)
		if(use_seg==3)
			BITSET(rfReg[0x0C], 0x00064004);
		else
			BITSET(rfReg[0x0C], 0x000F4004);
	else
		BITSET(rfReg[0x0C], 0x00050000);

	BITCLR(rfReg[0x0C], 0x80);
	if((use_lowif==1)||(use_seg==13))
		BITSET(rfReg[0x0C], 0x80);

	/*                               */
	rfReg[0x09] = Tcc353xRfGetMatchingReg(
	    &Tcc353xHandle[_moduleIndex][_diversityIndex], _freq_khz,
	    _tuneOption, bandIdx); 

	/*                                       */
	/*                   
                        
  */
	addressArray[0] = 0x04;
	addressArray[1] = 0x05;
	addressArray[2] = 0x07;
	addressArray[3] = 0x08;
	addressArray[4] = 0x09;
	addressArray[5] = 0x0C;

	BITSET(rfReg[0x08], 0x80000000);

	dataArray[0] = rfReg[0x04];
	dataArray[1] = rfReg[0x05];
	dataArray[2] = rfReg[0x07];
	dataArray[3] = rfReg[0x08];
	dataArray[4] = rfReg[0x09];
	dataArray[5] = rfReg[0x0C];

	arraySize = 6;

	Tcc353xRfWriteEx(_moduleIndex, _diversityIndex, &addressArray[0],
		         &dataArray[0], arraySize);

	BITCLR(rfReg[0x08], 0x80000000);
	Tcc353xRfWrite(_moduleIndex, _diversityIndex, 0x08, rfReg[0x08]);

}

I64U Tcc353xDiv64(I64U x, I64U y)
{
	I64U a, b, q, counter;

	q = 0;
	if (y != 0) {
		while (x >= y) {
			a = x >> 1;
			b = y;
			counter = 1;
			while (a >= b) {
				b <<= 1;
				counter <<= 1;
			}
			x -= b;
			q += counter;
		}
	}
	return q;
}
