
/*
 *
 Copyright (c) Eicon Networks, 2002.
 *
 This source file is supplied for the use with
 Eicon Networks range of DIVA Server Adapters.
 *
 Eicon File Revision :    2.1
 *
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2, or (at your option)
 any later version.
 *
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY
 implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.
 *
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */
#ifndef PC_INIT_H_
#define PC_INIT_H_
/*                                                                  */
/*
                                        
                   
                        
                                  
                                     
                                         
                                               
                                                       
                                                        
                                                                   
                              
                                             
                                                        
                                            
                                   
                                                               
                                
                                
                                                                     
                                                                         
                        
                             
                         
                       
                       
                                     
                                                  
                            
                                  
                                      
                    
                    
                      
                  
           
                              
              
            
                  
                                      
                                       
                                
                       
                       
                        
                                                  
*/
#define PCINIT_END_OF_LIST                0x00
#define PCINIT_MODEM_GUARD_TONE           0x01
#define PCINIT_MODEM_MIN_SPEED            0x02
#define PCINIT_MODEM_MAX_SPEED            0x03
#define PCINIT_MODEM_PROTOCOL_OPTIONS     0x04
#define PCINIT_FAX_OPTIONS                0x05
#define PCINIT_FAX_MAX_SPEED              0x06
#define PCINIT_MODEM_OPTIONS              0x07
#define PCINIT_MODEM_NEGOTIATION_MODE     0x08
#define PCINIT_MODEM_MODULATIONS_MASK     0x09
#define PCINIT_MODEM_TRANSMIT_LEVEL       0x0a
#define PCINIT_FAX_DISABLED_RESOLUTIONS   0x0b
#define PCINIT_FAX_MAX_RECORDING_WIDTH    0x0c
#define PCINIT_FAX_MAX_RECORDING_LENGTH   0x0d
#define PCINIT_FAX_MIN_SCANLINE_TIME      0x0e
#define PCINIT_US_EKTS_CACH_HANDLES       0x0f
#define PCINIT_US_EKTS_BEGIN_CONF         0x10
#define PCINIT_US_EKTS_DROP_CONF          0x11
#define PCINIT_US_EKTS_CALL_TRANSFER      0x12
#define PCINIT_RINGERTONE_OPTION          0x13
#define PCINIT_CARD_ADDRESS               0x14
#define PCINIT_FPGA_FEATURES              0x15
#define PCINIT_US_EKTS_MWI                0x16
#define PCINIT_MODEM_SPEAKER_CONTROL      0x17
#define PCINIT_MODEM_SPEAKER_VOLUME       0x18
#define PCINIT_MODEM_CARRIER_WAIT_TIME    0x19
#define PCINIT_MODEM_CARRIER_LOSS_TIME    0x1a
#define PCINIT_UNCHAN_B_MASK              0x1b
#define PCINIT_PART68_LIMITER             0x1c
#define PCINIT_XDI_FEATURES               0x1d
#define PCINIT_QSIG_DIALECT               0x1e
#define PCINIT_DISABLE_AUTOSPID_FLAG      0x1f
#define PCINIT_FORCE_VOICE_MAIL_ALERT     0x20
#define PCINIT_PIAFS_TURNAROUND_FRAMES    0x21
#define PCINIT_L2_COUNT                   0x22
#define PCINIT_QSIG_FEATURES              0x23
#define PCINIT_NO_SIGNALLING              0x24
#define PCINIT_CARD_SN                    0x25
#define PCINIT_CARD_PORT                  0x26
#define PCINIT_ALERTTO                    0x27
#define PCINIT_MODEM_EYE_SETUP            0x28
#define PCINIT_FAX_V34_OPTIONS            0x29
/*                                                                  */
#define PCINIT_MODEM_GUARD_TONE_NONE            0x00
#define PCINIT_MODEM_GUARD_TONE_550HZ           0x01
#define PCINIT_MODEM_GUARD_TONE_1800HZ          0x02
#define PCINIT_MODEM_GUARD_TONE_CHOICES         0x03
#define PCINIT_MODEMPROT_DISABLE_V42_V42BIS     0x0001
#define PCINIT_MODEMPROT_DISABLE_MNP_MNP5       0x0002
#define PCINIT_MODEMPROT_REQUIRE_PROTOCOL       0x0004
#define PCINIT_MODEMPROT_DISABLE_V42_DETECT     0x0008
#define PCINIT_MODEMPROT_DISABLE_COMPRESSION    0x0010
#define PCINIT_MODEMPROT_REQUIRE_PROTOCOL_V34UP 0x0020
#define PCINIT_MODEMPROT_NO_PROTOCOL_IF_1200    0x0100
#define PCINIT_MODEMPROT_BUFFER_IN_V42_DETECT   0x0200
#define PCINIT_MODEMPROT_DISABLE_V42_SREJ       0x0400
#define PCINIT_MODEMPROT_DISABLE_MNP3           0x0800
#define PCINIT_MODEMPROT_DISABLE_MNP4           0x1000
#define PCINIT_MODEMPROT_DISABLE_MNP10          0x2000
#define PCINIT_MODEMPROT_NO_PROTOCOL_IF_V22BIS  0x4000
#define PCINIT_MODEMPROT_NO_PROTOCOL_IF_V32BIS  0x8000
#define PCINIT_MODEMCONFIG_LEASED_LINE_MODE     0x00000001L
#define PCINIT_MODEMCONFIG_4_WIRE_OPERATION     0x00000002L
#define PCINIT_MODEMCONFIG_DISABLE_BUSY_DETECT  0x00000004L
#define PCINIT_MODEMCONFIG_DISABLE_CALLING_TONE 0x00000008L
#define PCINIT_MODEMCONFIG_DISABLE_ANSWER_TONE  0x00000010L
#define PCINIT_MODEMCONFIG_ENABLE_DIAL_TONE_DET 0x00000020L
#define PCINIT_MODEMCONFIG_USE_POTS_INTERFACE   0x00000040L
#define PCINIT_MODEMCONFIG_FORCE_RAY_TAYLOR_FAX 0x00000080L
#define PCINIT_MODEMCONFIG_DISABLE_RETRAIN      0x00000100L
#define PCINIT_MODEMCONFIG_DISABLE_STEPDOWN     0x00000200L
#define PCINIT_MODEMCONFIG_DISABLE_SPLIT_SPEED  0x00000400L
#define PCINIT_MODEMCONFIG_DISABLE_TRELLIS      0x00000800L
#define PCINIT_MODEMCONFIG_ALLOW_RDL_TEST_LOOP  0x00001000L
#define PCINIT_MODEMCONFIG_DISABLE_STEPUP       0x00002000L
#define PCINIT_MODEMCONFIG_DISABLE_FLUSH_TIMER  0x00004000L
#define PCINIT_MODEMCONFIG_REVERSE_DIRECTION    0x00008000L
#define PCINIT_MODEMCONFIG_DISABLE_TX_REDUCTION 0x00010000L
#define PCINIT_MODEMCONFIG_DISABLE_PRECODING    0x00020000L
#define PCINIT_MODEMCONFIG_DISABLE_PREEMPHASIS  0x00040000L
#define PCINIT_MODEMCONFIG_DISABLE_SHAPING      0x00080000L
#define PCINIT_MODEMCONFIG_DISABLE_NONLINEAR_EN 0x00100000L
#define PCINIT_MODEMCONFIG_DISABLE_MANUALREDUCT 0x00200000L
#define PCINIT_MODEMCONFIG_DISABLE_16_POINT_TRN 0x00400000L
#define PCINIT_MODEMCONFIG_DISABLE_2400_SYMBOLS 0x01000000L
#define PCINIT_MODEMCONFIG_DISABLE_2743_SYMBOLS 0x02000000L
#define PCINIT_MODEMCONFIG_DISABLE_2800_SYMBOLS 0x04000000L
#define PCINIT_MODEMCONFIG_DISABLE_3000_SYMBOLS 0x08000000L
#define PCINIT_MODEMCONFIG_DISABLE_3200_SYMBOLS 0x10000000L
#define PCINIT_MODEMCONFIG_DISABLE_3429_SYMBOLS 0x20000000L
#define PCINIT_MODEM_NEGOTIATE_HIGHEST          0x00
#define PCINIT_MODEM_NEGOTIATE_DISABLED         0x01
#define PCINIT_MODEM_NEGOTIATE_IN_CLASS         0x02
#define PCINIT_MODEM_NEGOTIATE_V100             0x03
#define PCINIT_MODEM_NEGOTIATE_V8               0x04
#define PCINIT_MODEM_NEGOTIATE_V8BIS            0x05
#define PCINIT_MODEM_NEGOTIATE_CHOICES          0x06
#define PCINIT_MODEMMODULATION_DISABLE_V21      0x00000001L
#define PCINIT_MODEMMODULATION_DISABLE_V23      0x00000002L
#define PCINIT_MODEMMODULATION_DISABLE_V22      0x00000004L
#define PCINIT_MODEMMODULATION_DISABLE_V22BIS   0x00000008L
#define PCINIT_MODEMMODULATION_DISABLE_V32      0x00000010L
#define PCINIT_MODEMMODULATION_DISABLE_V32BIS   0x00000020L
#define PCINIT_MODEMMODULATION_DISABLE_V34      0x00000040L
#define PCINIT_MODEMMODULATION_DISABLE_V90      0x00000080L
#define PCINIT_MODEMMODULATION_DISABLE_BELL103  0x00000100L
#define PCINIT_MODEMMODULATION_DISABLE_BELL212A 0x00000200L
#define PCINIT_MODEMMODULATION_DISABLE_VFC      0x00000400L
#define PCINIT_MODEMMODULATION_DISABLE_K56FLEX  0x00000800L
#define PCINIT_MODEMMODULATION_DISABLE_X2       0x00001000L
#define PCINIT_MODEMMODULATION_ENABLE_V29FDX    0x00010000L
#define PCINIT_MODEMMODULATION_ENABLE_V33       0x00020000L
#define PCINIT_MODEMMODULATION_ENABLE_V90A      0x00040000L
#define PCINIT_MODEM_TRANSMIT_LEVEL_CHOICES     0x10
#define PCINIT_MODEM_SPEAKER_OFF                0x00
#define PCINIT_MODEM_SPEAKER_DURING_TRAIN       0x01
#define PCINIT_MODEM_SPEAKER_TIL_CONNECT        0x02
#define PCINIT_MODEM_SPEAKER_ALWAYS_ON          0x03
#define PCINIT_MODEM_SPEAKER_CHOICES            0x04
#define PCINIT_MODEM_SPEAKER_VOLUME_MIN         0x00
#define PCINIT_MODEM_SPEAKER_VOLUME_LOW         0x01
#define PCINIT_MODEM_SPEAKER_VOLUME_HIGH        0x02
#define PCINIT_MODEM_SPEAKER_VOLUME_MAX         0x03
#define PCINIT_MODEM_SPEAKER_VOLUME_CHOICES     0x04
/*                                                                  */
#define PCINIT_FAXCONFIG_DISABLE_FINE           0x0001
#define PCINIT_FAXCONFIG_DISABLE_ECM            0x0002
#define PCINIT_FAXCONFIG_ECM_64_BYTES           0x0004
#define PCINIT_FAXCONFIG_DISABLE_2D_CODING      0x0008
#define PCINIT_FAXCONFIG_DISABLE_T6_CODING      0x0010
#define PCINIT_FAXCONFIG_DISABLE_UNCOMPR        0x0020
#define PCINIT_FAXCONFIG_REFUSE_POLLING         0x0040
#define PCINIT_FAXCONFIG_HIDE_TOTAL_PAGES       0x0080
#define PCINIT_FAXCONFIG_HIDE_ALL_HEADLINE      0x0100
#define PCINIT_FAXCONFIG_HIDE_PAGE_INFO         0x0180
#define PCINIT_FAXCONFIG_HEADLINE_OPTIONS_MASK  0x0180
#define PCINIT_FAXCONFIG_DISABLE_FEATURE_FALLBACK 0x0200
#define PCINIT_FAXCONFIG_V34FAX_CONTROL_RATE_1200 0x0800
#define PCINIT_FAXCONFIG_DISABLE_V34FAX         0x1000
#define PCINIT_FAXCONFIG_DISABLE_R8_0770_OR_200 0x01
#define PCINIT_FAXCONFIG_DISABLE_R8_1540        0x02
#define PCINIT_FAXCONFIG_DISABLE_R16_1540_OR_400 0x04
#define PCINIT_FAXCONFIG_DISABLE_R4_0385_OR_100 0x08
#define PCINIT_FAXCONFIG_DISABLE_300_300        0x10
#define PCINIT_FAXCONFIG_DISABLE_INCH_BASED     0x40
#define PCINIT_FAXCONFIG_DISABLE_METRIC_BASED   0x80
#define PCINIT_FAXCONFIG_REC_WIDTH_ISO_A3       0
#define PCINIT_FAXCONFIG_REC_WIDTH_ISO_B4       1
#define PCINIT_FAXCONFIG_REC_WIDTH_ISO_A4       2
#define PCINIT_FAXCONFIG_REC_WIDTH_COUNT        3
#define PCINIT_FAXCONFIG_REC_LENGTH_UNLIMITED   0
#define PCINIT_FAXCONFIG_REC_LENGTH_ISO_B4      1
#define PCINIT_FAXCONFIG_REC_LENGTH_ISO_A4      2
#define PCINIT_FAXCONFIG_REC_LENGTH_COUNT       3
#define PCINIT_FAXCONFIG_SCANLINE_TIME_00_00_00 0
#define PCINIT_FAXCONFIG_SCANLINE_TIME_05_05_05 1
#define PCINIT_FAXCONFIG_SCANLINE_TIME_10_05_05 2
#define PCINIT_FAXCONFIG_SCANLINE_TIME_10_10_10 3
#define PCINIT_FAXCONFIG_SCANLINE_TIME_20_10_10 4
#define PCINIT_FAXCONFIG_SCANLINE_TIME_20_20_20 5
#define PCINIT_FAXCONFIG_SCANLINE_TIME_40_20_20 6
#define PCINIT_FAXCONFIG_SCANLINE_TIME_40_40_40 7
#define PCINIT_FAXCONFIG_SCANLINE_TIME_RES_8    8
#define PCINIT_FAXCONFIG_SCANLINE_TIME_RES_9    9
#define PCINIT_FAXCONFIG_SCANLINE_TIME_RES_10   10
#define PCINIT_FAXCONFIG_SCANLINE_TIME_10_10_05 11
#define PCINIT_FAXCONFIG_SCANLINE_TIME_20_10_05 12
#define PCINIT_FAXCONFIG_SCANLINE_TIME_20_20_10 13
#define PCINIT_FAXCONFIG_SCANLINE_TIME_40_20_10 14
#define PCINIT_FAXCONFIG_SCANLINE_TIME_40_40_20 15
#define PCINIT_FAXCONFIG_SCANLINE_TIME_COUNT    16
#define PCINIT_FAXCONFIG_DISABLE_TX_REDUCTION   0x00010000L
#define PCINIT_FAXCONFIG_DISABLE_PRECODING      0x00020000L
#define PCINIT_FAXCONFIG_DISABLE_PREEMPHASIS    0x00040000L
#define PCINIT_FAXCONFIG_DISABLE_SHAPING        0x00080000L
#define PCINIT_FAXCONFIG_DISABLE_NONLINEAR_EN   0x00100000L
#define PCINIT_FAXCONFIG_DISABLE_MANUALREDUCT   0x00200000L
#define PCINIT_FAXCONFIG_DISABLE_16_POINT_TRN   0x00400000L
#define PCINIT_FAXCONFIG_DISABLE_2400_SYMBOLS   0x01000000L
#define PCINIT_FAXCONFIG_DISABLE_2743_SYMBOLS   0x02000000L
#define PCINIT_FAXCONFIG_DISABLE_2800_SYMBOLS   0x04000000L
#define PCINIT_FAXCONFIG_DISABLE_3000_SYMBOLS   0x08000000L
#define PCINIT_FAXCONFIG_DISABLE_3200_SYMBOLS   0x10000000L
#define PCINIT_FAXCONFIG_DISABLE_3429_SYMBOLS   0x20000000L
/*                                                                          */
#define PCINIT_XDI_CMA_FOR_ALL_NL_PRIMITIVES    0x01
/*                                                                          */
#define PCINIT_FPGA_PLX_ACCESS_SUPPORTED        0x01
/*                                                                          */
#endif
/*                                                                          */
