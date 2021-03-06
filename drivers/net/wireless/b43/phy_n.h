#ifndef B43_NPHY_H_
#define B43_NPHY_H_

#include "phy_common.h"


/*                  */

#define B43_NPHY_BBCFG				B43_PHY_N(0x001) /*           */
#define  B43_NPHY_BBCFG_RSTCCA			0x4000 /*           */
#define  B43_NPHY_BBCFG_RSTRX			0x8000 /*          */
#define B43_NPHY_CHANNEL			B43_PHY_N(0x005) /*         */
#define B43_NPHY_TXERR				B43_PHY_N(0x007) /*          */
#define B43_NPHY_BANDCTL			B43_PHY_N(0x009) /*              */
#define  B43_NPHY_BANDCTL_5GHZ			0x0001 /*                   */
#define B43_NPHY_4WI_ADDR			B43_PHY_N(0x00B) /*                       */
#define B43_NPHY_4WI_DATAHI			B43_PHY_N(0x00C) /*                         */
#define B43_NPHY_4WI_DATALO			B43_PHY_N(0x00D) /*                        */
#define B43_NPHY_BIST_STAT0			B43_PHY_N(0x00E) /*                             */
#define B43_NPHY_BIST_STAT1			B43_PHY_N(0x00F) /*                             */

#define B43_NPHY_C1_DESPWR			B43_PHY_N(0x018) /*                      */
#define B43_NPHY_C1_CCK_DESPWR			B43_PHY_N(0x019) /*                          */
#define B43_NPHY_C1_BCLIPBKOFF			B43_PHY_N(0x01A) /*                            */
#define B43_NPHY_C1_CCK_BCLIPBKOFF		B43_PHY_N(0x01B) /*                                */
#define B43_NPHY_C1_CGAINI			B43_PHY_N(0x01C) /*                          */
#define  B43_NPHY_C1_CGAINI_GAINBKOFF		0x001F /*              */
#define  B43_NPHY_C1_CGAINI_GAINBKOFF_SHIFT	0
#define  B43_NPHY_C1_CGAINI_CLIPGBKOFF		0x03E0 /*                   */
#define  B43_NPHY_C1_CGAINI_CLIPGBKOFF_SHIFT	5
#define  B43_NPHY_C1_CGAINI_GAINSTEP		0x1C00 /*           */
#define  B43_NPHY_C1_CGAINI_GAINSTEP_SHIFT	10
#define  B43_NPHY_C1_CGAINI_CL2DETECT		0x2000 /*                    */
#define B43_NPHY_C1_CCK_CGAINI			B43_PHY_N(0x01D) /*                              */
#define  B43_NPHY_C1_CCK_CGAINI_GAINBKOFF	0x001F /*              */
#define  B43_NPHY_C1_CCK_CGAINI_CLIPGBKOFF	0x01E0 /*                              */
#define B43_NPHY_C1_MINMAX_GAIN			B43_PHY_N(0x01E) /*                     */
#define  B43_NPHY_C1_MINGAIN			0x00FF /*              */
#define  B43_NPHY_C1_MINGAIN_SHIFT		0
#define  B43_NPHY_C1_MAXGAIN			0xFF00 /*              */
#define  B43_NPHY_C1_MAXGAIN_SHIFT		8
#define B43_NPHY_C1_CCK_MINMAX_GAIN		B43_PHY_N(0x01F) /*                         */
#define  B43_NPHY_C1_CCK_MINGAIN		0x00FF /*              */
#define  B43_NPHY_C1_CCK_MINGAIN_SHIFT		0
#define  B43_NPHY_C1_CCK_MAXGAIN		0xFF00 /*              */
#define  B43_NPHY_C1_CCK_MAXGAIN_SHIFT		8
#define B43_NPHY_C1_INITGAIN			B43_PHY_N(0x020) /*                          */
#define  B43_NPHY_C1_INITGAIN_EXTLNA		0x0001 /*                    */
#define  B43_NPHY_C1_INITGAIN_LNA		0x0006 /*           */
#define  B43_NPHY_C1_INITGAIN_LNAIDX_SHIFT	1
#define  B43_NPHY_C1_INITGAIN_HPVGA1		0x0078 /*              */
#define  B43_NPHY_C1_INITGAIN_HPVGA1_SHIFT	3
#define  B43_NPHY_C1_INITGAIN_HPVGA2		0x0F80 /*              */
#define  B43_NPHY_C1_INITGAIN_HPVGA2_SHIFT	7
#define  B43_NPHY_C1_INITGAIN_TRRX		0x1000 /*             */
#define  B43_NPHY_C1_INITGAIN_TRTX		0x2000 /*             */
#define B43_NPHY_C1_CLIP1_HIGAIN		B43_PHY_N(0x021) /*                             */
#define B43_NPHY_C1_CLIP1_MEDGAIN		B43_PHY_N(0x022) /*                               */
#define B43_NPHY_C1_CLIP1_LOGAIN		B43_PHY_N(0x023) /*                            */
#define B43_NPHY_C1_CLIP2_GAIN			B43_PHY_N(0x024) /*                        */
#define B43_NPHY_C1_FILTERGAIN			B43_PHY_N(0x025) /*                    */
#define B43_NPHY_C1_LPF_QHPF_BW			B43_PHY_N(0x026) /*                             */
#define B43_NPHY_C1_CLIPWBTHRES			B43_PHY_N(0x027) /*                                */
#define  B43_NPHY_C1_CLIPWBTHRES_CLIP2		0x003F /*        */
#define  B43_NPHY_C1_CLIPWBTHRES_CLIP2_SHIFT	0
#define  B43_NPHY_C1_CLIPWBTHRES_CLIP1		0x0FC0 /*        */
#define  B43_NPHY_C1_CLIPWBTHRES_CLIP1_SHIFT	6
#define B43_NPHY_C1_W1THRES			B43_PHY_N(0x028) /*                     */
#define B43_NPHY_C1_EDTHRES			B43_PHY_N(0x029) /*                     */
#define B43_NPHY_C1_SMSIGTHRES			B43_PHY_N(0x02A) /*                            */
#define B43_NPHY_C1_NBCLIPTHRES			B43_PHY_N(0x02B) /*                          */
#define B43_NPHY_C1_CLIP1THRES			B43_PHY_N(0x02C) /*                        */
#define B43_NPHY_C1_CLIP2THRES			B43_PHY_N(0x02D) /*                        */

#define B43_NPHY_C2_DESPWR			B43_PHY_N(0x02E) /*                      */
#define B43_NPHY_C2_CCK_DESPWR			B43_PHY_N(0x02F) /*                          */
#define B43_NPHY_C2_BCLIPBKOFF			B43_PHY_N(0x030) /*                            */
#define B43_NPHY_C2_CCK_BCLIPBKOFF		B43_PHY_N(0x031) /*                                */
#define B43_NPHY_C2_CGAINI			B43_PHY_N(0x032) /*                          */
#define  B43_NPHY_C2_CGAINI_GAINBKOFF		0x001F /*              */
#define  B43_NPHY_C2_CGAINI_GAINBKOFF_SHIFT	0
#define  B43_NPHY_C2_CGAINI_CLIPGBKOFF		0x03E0 /*                   */
#define  B43_NPHY_C2_CGAINI_CLIPGBKOFF_SHIFT	5
#define  B43_NPHY_C2_CGAINI_GAINSTEP		0x1C00 /*           */
#define  B43_NPHY_C2_CGAINI_GAINSTEP_SHIFT	10
#define  B43_NPHY_C2_CGAINI_CL2DETECT		0x2000 /*                    */
#define B43_NPHY_C2_CCK_CGAINI			B43_PHY_N(0x033) /*                              */
#define  B43_NPHY_C2_CCK_CGAINI_GAINBKOFF	0x001F /*              */
#define  B43_NPHY_C2_CCK_CGAINI_CLIPGBKOFF	0x01E0 /*                              */
#define B43_NPHY_C2_MINMAX_GAIN			B43_PHY_N(0x034) /*                     */
#define  B43_NPHY_C2_MINGAIN			0x00FF /*              */
#define  B43_NPHY_C2_MINGAIN_SHIFT		0
#define  B43_NPHY_C2_MAXGAIN			0xFF00 /*              */
#define  B43_NPHY_C2_MAXGAIN_SHIFT		8
#define B43_NPHY_C2_CCK_MINMAX_GAIN		B43_PHY_N(0x035) /*                         */
#define  B43_NPHY_C2_CCK_MINGAIN		0x00FF /*              */
#define  B43_NPHY_C2_CCK_MINGAIN_SHIFT		0
#define  B43_NPHY_C2_CCK_MAXGAIN		0xFF00 /*              */
#define  B43_NPHY_C2_CCK_MAXGAIN_SHIFT		8
#define B43_NPHY_C2_INITGAIN			B43_PHY_N(0x036) /*                          */
#define  B43_NPHY_C2_INITGAIN_EXTLNA		0x0001 /*                    */
#define  B43_NPHY_C2_INITGAIN_LNA		0x0006 /*           */
#define  B43_NPHY_C2_INITGAIN_LNAIDX_SHIFT	1
#define  B43_NPHY_C2_INITGAIN_HPVGA1		0x0078 /*              */
#define  B43_NPHY_C2_INITGAIN_HPVGA1_SHIFT	3
#define  B43_NPHY_C2_INITGAIN_HPVGA2		0x0F80 /*              */
#define  B43_NPHY_C2_INITGAIN_HPVGA2_SHIFT	7
#define  B43_NPHY_C2_INITGAIN_TRRX		0x1000 /*             */
#define  B43_NPHY_C2_INITGAIN_TRTX		0x2000 /*             */
#define B43_NPHY_C2_CLIP1_HIGAIN		B43_PHY_N(0x037) /*                             */
#define B43_NPHY_C2_CLIP1_MEDGAIN		B43_PHY_N(0x038) /*                               */
#define B43_NPHY_C2_CLIP1_LOGAIN		B43_PHY_N(0x039) /*                            */
#define B43_NPHY_C2_CLIP2_GAIN			B43_PHY_N(0x03A) /*                        */
#define B43_NPHY_C2_FILTERGAIN			B43_PHY_N(0x03B) /*                    */
#define B43_NPHY_C2_LPF_QHPF_BW			B43_PHY_N(0x03C) /*                             */
#define B43_NPHY_C2_CLIPWBTHRES			B43_PHY_N(0x03D) /*                                */
#define  B43_NPHY_C2_CLIPWBTHRES_CLIP2		0x003F /*        */
#define  B43_NPHY_C2_CLIPWBTHRES_CLIP2_SHIFT	0
#define  B43_NPHY_C2_CLIPWBTHRES_CLIP1		0x0FC0 /*        */
#define  B43_NPHY_C2_CLIPWBTHRES_CLIP1_SHIFT	6
#define B43_NPHY_C2_W1THRES			B43_PHY_N(0x03E) /*                     */
#define B43_NPHY_C2_EDTHRES			B43_PHY_N(0x03F) /*                     */
#define B43_NPHY_C2_SMSIGTHRES			B43_PHY_N(0x040) /*                            */
#define B43_NPHY_C2_NBCLIPTHRES			B43_PHY_N(0x041) /*                          */
#define B43_NPHY_C2_CLIP1THRES			B43_PHY_N(0x042) /*                        */
#define B43_NPHY_C2_CLIP2THRES			B43_PHY_N(0x043) /*                        */

#define B43_NPHY_CRS_THRES1			B43_PHY_N(0x044) /*                 */
#define B43_NPHY_CRS_THRES2			B43_PHY_N(0x045) /*                 */
#define B43_NPHY_CRS_THRES3			B43_PHY_N(0x046) /*                 */
#define B43_NPHY_CRSCTL				B43_PHY_N(0x047) /*             */
#define B43_NPHY_DCFADDR			B43_PHY_N(0x048) /*                   */
#define B43_NPHY_RXF20_NUM0			B43_PHY_N(0x049) /*                          */
#define B43_NPHY_RXF20_NUM1			B43_PHY_N(0x04A) /*                          */
#define B43_NPHY_RXF20_NUM2			B43_PHY_N(0x04B) /*                          */
#define B43_NPHY_RXF20_DENOM0			B43_PHY_N(0x04C) /*                            */
#define B43_NPHY_RXF20_DENOM1			B43_PHY_N(0x04D) /*                            */
#define B43_NPHY_RXF20_NUM10			B43_PHY_N(0x04E) /*                           */
#define B43_NPHY_RXF20_NUM11			B43_PHY_N(0x04F) /*                           */
#define B43_NPHY_RXF20_NUM12			B43_PHY_N(0x050) /*                           */
#define B43_NPHY_RXF20_DENOM10			B43_PHY_N(0x051) /*                             */
#define B43_NPHY_RXF20_DENOM11			B43_PHY_N(0x052) /*                             */
#define B43_NPHY_RXF40_NUM0			B43_PHY_N(0x053) /*                          */
#define B43_NPHY_RXF40_NUM1			B43_PHY_N(0x054) /*                          */
#define B43_NPHY_RXF40_NUM2			B43_PHY_N(0x055) /*                          */
#define B43_NPHY_RXF40_DENOM0			B43_PHY_N(0x056) /*                            */
#define B43_NPHY_RXF40_DENOM1			B43_PHY_N(0x057) /*                            */
#define B43_NPHY_RXF40_NUM10			B43_PHY_N(0x058) /*                           */
#define B43_NPHY_RXF40_NUM11			B43_PHY_N(0x059) /*                           */
#define B43_NPHY_RXF40_NUM12			B43_PHY_N(0x05A) /*                           */
#define B43_NPHY_RXF40_DENOM10			B43_PHY_N(0x05B) /*                             */
#define B43_NPHY_RXF40_DENOM11			B43_PHY_N(0x05C) /*                             */
#define B43_NPHY_PPROC_RSTLEN			B43_PHY_N(0x060) /*                                */
#define B43_NPHY_INITCARR_DLEN			B43_PHY_N(0x061) /*                                  */
#define B43_NPHY_CLIP1CARR_DLEN			B43_PHY_N(0x062) /*                                */
#define B43_NPHY_CLIP2CARR_DLEN			B43_PHY_N(0x063) /*                                */
#define B43_NPHY_INITGAIN_SLEN			B43_PHY_N(0x064) /*                            */
#define B43_NPHY_CLIP1GAIN_SLEN			B43_PHY_N(0x065) /*                          */
#define B43_NPHY_CLIP2GAIN_SLEN			B43_PHY_N(0x066) /*                          */
#define B43_NPHY_PACKGAIN_SLEN			B43_PHY_N(0x067) /*                           */
#define B43_NPHY_CARRSRC_TLEN			B43_PHY_N(0x068) /*                               */
#define B43_NPHY_TISRC_TLEN			B43_PHY_N(0x069) /*                              */
#define B43_NPHY_ENDROP_TLEN			B43_PHY_N(0x06A) /*                            */
#define B43_NPHY_CLIP1_NBDWELL_LEN		B43_PHY_N(0x06B) /*                       */
#define B43_NPHY_CLIP2_NBDWELL_LEN		B43_PHY_N(0x06C) /*                       */
#define B43_NPHY_W1CLIP1_DWELL_LEN		B43_PHY_N(0x06D) /*                       */
#define B43_NPHY_W1CLIP2_DWELL_LEN		B43_PHY_N(0x06E) /*                       */
#define B43_NPHY_W2CLIP1_DWELL_LEN		B43_PHY_N(0x06F) /*                       */
#define B43_NPHY_PLOAD_CSENSE_EXTLEN		B43_PHY_N(0x070) /*                                        */
#define B43_NPHY_EDROP_CSENSE_EXTLEN		B43_PHY_N(0x071) /*                                            */
#define B43_NPHY_TABLE_ADDR			B43_PHY_N(0x072) /*               */
#define B43_NPHY_TABLE_DATALO			B43_PHY_N(0x073) /*                */
#define B43_NPHY_TABLE_DATAHI			B43_PHY_N(0x074) /*                 */
#define B43_NPHY_WWISE_LENIDX			B43_PHY_N(0x075) /*                    */
#define B43_NPHY_TGNSYNC_LENIDX			B43_PHY_N(0x076) /*                      */
#define B43_NPHY_TXMACIF_HOLDOFF		B43_PHY_N(0x077) /*                    */
#define B43_NPHY_RFCTL_CMD			B43_PHY_N(0x078) /*                      */
#define  B43_NPHY_RFCTL_CMD_START		0x0001 /*                */
#define  B43_NPHY_RFCTL_CMD_RXTX		0x0002 /*       */
#define  B43_NPHY_RFCTL_CMD_CORESEL		0x0038 /*             */
#define  B43_NPHY_RFCTL_CMD_CORESEL_SHIFT	3
#define  B43_NPHY_RFCTL_CMD_PORFORCE		0x0040 /*           */
#define  B43_NPHY_RFCTL_CMD_OEPORFORCE		0x0080 /*              */
#define  B43_NPHY_RFCTL_CMD_RXEN		0x0100 /*           */
#define  B43_NPHY_RFCTL_CMD_TXEN		0x0200 /*           */
#define  B43_NPHY_RFCTL_CMD_CHIP0PU		0x0400 /*          */
#define  B43_NPHY_RFCTL_CMD_EN			0x0800 /*               */
#define  B43_NPHY_RFCTL_CMD_SEQENCORE		0xF000 /*             */
#define  B43_NPHY_RFCTL_CMD_SEQENCORE_SHIFT	12
#define B43_NPHY_RFCTL_RSSIO1			B43_PHY_N(0x07A) /*                            */
#define  B43_NPHY_RFCTL_RSSIO1_RXPD		0x0001 /*       */
#define  B43_NPHY_RFCTL_RSSIO1_TXPD		0x0002 /*       */
#define  B43_NPHY_RFCTL_RSSIO1_PAPD		0x0004 /*       */
#define  B43_NPHY_RFCTL_RSSIO1_RSSICTL		0x0030 /*              */
#define  B43_NPHY_RFCTL_RSSIO1_LPFBW		0x00C0 /*               */
#define  B43_NPHY_RFCTL_RSSIO1_HPFBWHI		0x0100 /*                    */
#define  B43_NPHY_RFCTL_RSSIO1_HIQDISCO		0x0200 /*              */
#define B43_NPHY_RFCTL_RXG1			B43_PHY_N(0x07B) /*                        */
#define B43_NPHY_RFCTL_TXG1			B43_PHY_N(0x07C) /*                        */
#define B43_NPHY_RFCTL_RSSIO2			B43_PHY_N(0x07D) /*                            */
#define  B43_NPHY_RFCTL_RSSIO2_RXPD		0x0001 /*       */
#define  B43_NPHY_RFCTL_RSSIO2_TXPD		0x0002 /*       */
#define  B43_NPHY_RFCTL_RSSIO2_PAPD		0x0004 /*       */
#define  B43_NPHY_RFCTL_RSSIO2_RSSICTL		0x0030 /*              */
#define  B43_NPHY_RFCTL_RSSIO2_LPFBW		0x00C0 /*               */
#define  B43_NPHY_RFCTL_RSSIO2_HPFBWHI		0x0100 /*                    */
#define  B43_NPHY_RFCTL_RSSIO2_HIQDISCO		0x0200 /*              */
#define B43_NPHY_RFCTL_RXG2			B43_PHY_N(0x07E) /*                        */
#define B43_NPHY_RFCTL_TXG2			B43_PHY_N(0x07F) /*                        */
#define B43_NPHY_RFCTL_RSSIO3			B43_PHY_N(0x080) /*                            */
#define  B43_NPHY_RFCTL_RSSIO3_RXPD		0x0001 /*       */
#define  B43_NPHY_RFCTL_RSSIO3_TXPD		0x0002 /*       */
#define  B43_NPHY_RFCTL_RSSIO3_PAPD		0x0004 /*       */
#define  B43_NPHY_RFCTL_RSSIO3_RSSICTL		0x0030 /*              */
#define  B43_NPHY_RFCTL_RSSIO3_LPFBW		0x00C0 /*               */
#define  B43_NPHY_RFCTL_RSSIO3_HPFBWHI		0x0100 /*                    */
#define  B43_NPHY_RFCTL_RSSIO3_HIQDISCO		0x0200 /*              */
#define B43_NPHY_RFCTL_RXG3			B43_PHY_N(0x081) /*                        */
#define B43_NPHY_RFCTL_TXG3			B43_PHY_N(0x082) /*                        */
#define B43_NPHY_RFCTL_RSSIO4			B43_PHY_N(0x083) /*                            */
#define  B43_NPHY_RFCTL_RSSIO4_RXPD		0x0001 /*       */
#define  B43_NPHY_RFCTL_RSSIO4_TXPD		0x0002 /*       */
#define  B43_NPHY_RFCTL_RSSIO4_PAPD		0x0004 /*       */
#define  B43_NPHY_RFCTL_RSSIO4_RSSICTL		0x0030 /*              */
#define  B43_NPHY_RFCTL_RSSIO4_LPFBW		0x00C0 /*               */
#define  B43_NPHY_RFCTL_RSSIO4_HPFBWHI		0x0100 /*                    */
#define  B43_NPHY_RFCTL_RSSIO4_HIQDISCO		0x0200 /*              */
#define B43_NPHY_RFCTL_RXG4			B43_PHY_N(0x084) /*                        */
#define B43_NPHY_RFCTL_TXG4			B43_PHY_N(0x085) /*                        */
#define B43_NPHY_C1_TXIQ_COMP_OFF		B43_PHY_N(0x087) /*                           */
#define B43_NPHY_C2_TXIQ_COMP_OFF		B43_PHY_N(0x088) /*                           */
#define B43_NPHY_C1_TXCTL			B43_PHY_N(0x08B) /*                   */
#define B43_NPHY_C2_TXCTL			B43_PHY_N(0x08C) /*                   */
#define B43_NPHY_AFECTL_OVER1			B43_PHY_N(0x08F) /*                        */
#define B43_NPHY_SCRAM_SIGCTL			B43_PHY_N(0x090) /*                      */
#define  B43_NPHY_SCRAM_SIGCTL_INITST		0x007F /*                     */
#define  B43_NPHY_SCRAM_SIGCTL_INITST_SHIFT	0
#define  B43_NPHY_SCRAM_SIGCTL_SCM		0x0080 /*                    */
#define  B43_NPHY_SCRAM_SIGCTL_SICE		0x0100 /*                            */
#define  B43_NPHY_SCRAM_SIGCTL_START		0xFE00 /*                 */
#define  B43_NPHY_SCRAM_SIGCTL_START_SHIFT	9
#define B43_NPHY_RFCTL_INTC1			B43_PHY_N(0x091) /*                     */
#define B43_NPHY_RFCTL_INTC2			B43_PHY_N(0x092) /*                     */
#define B43_NPHY_RFCTL_INTC3			B43_PHY_N(0x093) /*                     */
#define B43_NPHY_RFCTL_INTC4			B43_PHY_N(0x094) /*                     */
#define B43_NPHY_NRDTO_WWISE			B43_PHY_N(0x095) /*                   */
#define B43_NPHY_NRDTO_TGNSYNC			B43_PHY_N(0x096) /*                     */
#define B43_NPHY_SIGFMOD_WWISE			B43_PHY_N(0x097) /*                        */
#define B43_NPHY_LEG_SIGFMOD_11N		B43_PHY_N(0x098) /*                             */
#define B43_NPHY_HT_SIGFMOD_11N			B43_PHY_N(0x099) /*                         */
#define B43_NPHY_C1_RXIQ_COMPA0			B43_PHY_N(0x09A) /*                       */
#define B43_NPHY_C1_RXIQ_COMPB0			B43_PHY_N(0x09B) /*                       */
#define B43_NPHY_C2_RXIQ_COMPA1			B43_PHY_N(0x09C) /*                       */
#define B43_NPHY_C2_RXIQ_COMPB1			B43_PHY_N(0x09D) /*                       */
#define B43_NPHY_RXCTL				B43_PHY_N(0x0A0) /*            */
#define  B43_NPHY_RXCTL_BSELU20			0x0010 /*                      */
#define  B43_NPHY_RXCTL_RIFSEN			0x0080 /*             */
#define B43_NPHY_RFSEQMODE			B43_PHY_N(0x0A1) /*             */
#define  B43_NPHY_RFSEQMODE_CAOVER		0x0001 /*                      */
#define  B43_NPHY_RFSEQMODE_TROVER		0x0002 /*                  */
#define B43_NPHY_RFSEQCA			B43_PHY_N(0x0A2) /*                    */
#define  B43_NPHY_RFSEQCA_TXEN			0x000F /*           */
#define  B43_NPHY_RFSEQCA_TXEN_SHIFT		0
#define  B43_NPHY_RFSEQCA_RXEN			0x00F0 /*           */
#define  B43_NPHY_RFSEQCA_RXEN_SHIFT		4
#define  B43_NPHY_RFSEQCA_TXDIS			0x0F00 /*            */
#define  B43_NPHY_RFSEQCA_TXDIS_SHIFT		8
#define  B43_NPHY_RFSEQCA_RXDIS			0xF000 /*            */
#define  B43_NPHY_RFSEQCA_RXDIS_SHIFT		12
#define B43_NPHY_RFSEQTR			B43_PHY_N(0x0A3) /*                */
#define  B43_NPHY_RFSEQTR_RX2TX			0x0001 /*       */
#define  B43_NPHY_RFSEQTR_TX2RX			0x0002 /*       */
#define  B43_NPHY_RFSEQTR_UPGH			0x0004 /*               */
#define  B43_NPHY_RFSEQTR_UPGL			0x0008 /*               */
#define  B43_NPHY_RFSEQTR_UPGU			0x0010 /*               */
#define  B43_NPHY_RFSEQTR_RST2RX		0x0020 /*             */
#define B43_NPHY_RFSEQST			B43_PHY_N(0x0A4) /*                                        */
#define B43_NPHY_AFECTL_OVER			B43_PHY_N(0x0A5) /*                      */
#define B43_NPHY_AFECTL_C1			B43_PHY_N(0x0A6) /*                    */
#define B43_NPHY_AFECTL_C2			B43_PHY_N(0x0A7) /*                    */
#define B43_NPHY_AFECTL_C3			B43_PHY_N(0x0A8) /*                    */
#define B43_NPHY_AFECTL_C4			B43_PHY_N(0x0A9) /*                    */
#define B43_NPHY_AFECTL_DACGAIN1		B43_PHY_N(0x0AA) /*                        */
#define B43_NPHY_AFECTL_DACGAIN2		B43_PHY_N(0x0AB) /*                        */
#define B43_NPHY_AFECTL_DACGAIN3		B43_PHY_N(0x0AC) /*                        */
#define B43_NPHY_AFECTL_DACGAIN4		B43_PHY_N(0x0AD) /*                        */
#define B43_NPHY_STR_ADDR1			B43_PHY_N(0x0AE) /*               */
#define B43_NPHY_STR_ADDR2			B43_PHY_N(0x0AF) /*               */
#define B43_NPHY_CLASSCTL			B43_PHY_N(0x0B0) /*                    */
#define  B43_NPHY_CLASSCTL_CCKEN		0x0001 /*            */
#define  B43_NPHY_CLASSCTL_OFDMEN		0x0002 /*             */
#define  B43_NPHY_CLASSCTL_WAITEDEN		0x0004 /*               */
#define B43_NPHY_IQFLIP				B43_PHY_N(0x0B1) /*          */
#define  B43_NPHY_IQFLIP_ADC1			0x0001 /*      */
#define  B43_NPHY_IQFLIP_ADC2			0x0010 /*      */
#define B43_NPHY_SISO_SNR_THRES			B43_PHY_N(0x0B2) /*                    */
#define B43_NPHY_SIGMA_N_MULT			B43_PHY_N(0x0B3) /*                    */
#define B43_NPHY_TXMACDELAY			B43_PHY_N(0x0B4) /*              */
#define B43_NPHY_TXFRAMEDELAY			B43_PHY_N(0x0B5) /*                */
#define B43_NPHY_MLPARM				B43_PHY_N(0x0B6) /*               */
#define B43_NPHY_MLCTL				B43_PHY_N(0x0B7) /*            */
#define B43_NPHY_WWISE_20NCYCDAT		B43_PHY_N(0x0B8) /*                     */
#define B43_NPHY_WWISE_40NCYCDAT		B43_PHY_N(0x0B9) /*                     */
#define B43_NPHY_TGNSYNC_20NCYCDAT		B43_PHY_N(0x0BA) /*                       */
#define B43_NPHY_TGNSYNC_40NCYCDAT		B43_PHY_N(0x0BB) /*                       */
#define B43_NPHY_INITSWIZP			B43_PHY_N(0x0BC) /*                         */
#define B43_NPHY_TXTAILCNT			B43_PHY_N(0x0BD) /*                     */
#define B43_NPHY_BPHY_CTL1			B43_PHY_N(0x0BE) /*                 */
#define B43_NPHY_BPHY_CTL2			B43_PHY_N(0x0BF) /*                 */
#define  B43_NPHY_BPHY_CTL2_LUT			0x001F /*           */
#define  B43_NPHY_BPHY_CTL2_LUT_SHIFT		0
#define  B43_NPHY_BPHY_CTL2_MACDEL		0x7FE0 /*           */
#define  B43_NPHY_BPHY_CTL2_MACDEL_SHIFT	5
#define B43_NPHY_IQLOCAL_CMD			B43_PHY_N(0x0C0) /*                    */
#define  B43_NPHY_IQLOCAL_CMD_EN		0x8000
#define B43_NPHY_IQLOCAL_CMDNNUM		B43_PHY_N(0x0C1) /*                          */
#define B43_NPHY_IQLOCAL_CMDGCTL		B43_PHY_N(0x0C2) /*                              */
#define B43_NPHY_SAMP_CMD			B43_PHY_N(0x0C3) /*                */
#define  B43_NPHY_SAMP_CMD_STOP			0x0002 /*      */
#define B43_NPHY_SAMP_LOOPCNT			B43_PHY_N(0x0C4) /*                   */
#define B43_NPHY_SAMP_WAITCNT			B43_PHY_N(0x0C5) /*                   */
#define B43_NPHY_SAMP_DEPCNT			B43_PHY_N(0x0C6) /*                    */
#define B43_NPHY_SAMP_STAT			B43_PHY_N(0x0C7) /*               */
#define B43_NPHY_GPIO_LOOEN			B43_PHY_N(0x0C8) /*                     */
#define B43_NPHY_GPIO_HIOEN			B43_PHY_N(0x0C9) /*                      */
#define B43_NPHY_GPIO_SEL			B43_PHY_N(0x0CA) /*             */
#define B43_NPHY_GPIO_CLKCTL			B43_PHY_N(0x0CB) /*                    */
#define B43_NPHY_TXF_20CO_AS0			B43_PHY_N(0x0CC) /*                              */
#define B43_NPHY_TXF_20CO_AS1			B43_PHY_N(0x0CD) /*                              */
#define B43_NPHY_TXF_20CO_AS2			B43_PHY_N(0x0CE) /*                              */
#define B43_NPHY_TXF_20CO_B32S0			B43_PHY_N(0x0CF) /*                                */
#define B43_NPHY_TXF_20CO_B1S0			B43_PHY_N(0x0D0) /*                               */
#define B43_NPHY_TXF_20CO_B32S1			B43_PHY_N(0x0D1) /*                                */
#define B43_NPHY_TXF_20CO_B1S1			B43_PHY_N(0x0D2) /*                               */
#define B43_NPHY_TXF_20CO_B32S2			B43_PHY_N(0x0D3) /*                                */
#define B43_NPHY_TXF_20CO_B1S2			B43_PHY_N(0x0D4) /*                               */
#define B43_NPHY_SIGFLDTOL			B43_PHY_N(0x0D5) /*                      */
#define B43_NPHY_TXSERFLD			B43_PHY_N(0x0D6) /*                  */
#define B43_NPHY_AFESEQ_RX2TX_PUD		B43_PHY_N(0x0D7) /*                                   */
#define B43_NPHY_AFESEQ_TX2RX_PUD		B43_PHY_N(0x0D8) /*                                   */
#define B43_NPHY_TGNSYNC_SCRAMI0		B43_PHY_N(0x0D9) /*                      */
#define B43_NPHY_TGNSYNC_SCRAMI1		B43_PHY_N(0x0DA) /*                      */
#define B43_NPHY_INITSWIZPATTLEG		B43_PHY_N(0x0DB) /*                             */
#define B43_NPHY_BPHY_CTL3			B43_PHY_N(0x0DC) /*                 */
#define  B43_NPHY_BPHY_CTL3_SCALE		0x00FF /*       */
#define  B43_NPHY_BPHY_CTL3_SCALE_SHIFT		0
#define  B43_NPHY_BPHY_CTL3_FSC			0xFF00 /*                         */
#define  B43_NPHY_BPHY_CTL3_FSC_SHIFT		8
#define B43_NPHY_BPHY_CTL4			B43_PHY_N(0x0DD) /*                 */
#define B43_NPHY_C1_TXBBMULT			B43_PHY_N(0x0DE) /*                         */
#define B43_NPHY_C2_TXBBMULT			B43_PHY_N(0x0DF) /*                         */
#define B43_NPHY_TXF_40CO_AS0			B43_PHY_N(0x0E1) /*                              */
#define B43_NPHY_TXF_40CO_AS1			B43_PHY_N(0x0E2) /*                              */
#define B43_NPHY_TXF_40CO_AS2			B43_PHY_N(0x0E3) /*                              */
#define B43_NPHY_TXF_40CO_B32S0			B43_PHY_N(0x0E4) /*                                */
#define B43_NPHY_TXF_40CO_B1S0			B43_PHY_N(0x0E5) /*                               */
#define B43_NPHY_TXF_40CO_B32S1			B43_PHY_N(0x0E6) /*                                */
#define B43_NPHY_TXF_40CO_B1S1			B43_PHY_N(0x0E7) /*                               */
#define B43_NPHY_TXF_40CO_B32S2			B43_PHY_N(0x0E8) /*                                */
#define B43_NPHY_TXF_40CO_B1S2			B43_PHY_N(0x0E9) /*                               */
#define B43_NPHY_BIST_STAT2			B43_PHY_N(0x0EA) /*               */
#define B43_NPHY_BIST_STAT3			B43_PHY_N(0x0EB) /*               */
#define B43_NPHY_RFCTL_OVER			B43_PHY_N(0x0EC) /*                     */
#define B43_NPHY_MIMOCFG			B43_PHY_N(0x0ED) /*             */
#define  B43_NPHY_MIMOCFG_GFMIX			0x0004 /*                          */
#define  B43_NPHY_MIMOCFG_AUTO			0x0100 /*                            */
#define B43_NPHY_RADAR_BLNKCTL			B43_PHY_N(0x0EE) /*                     */
#define B43_NPHY_A0RADAR_FIFOCTL		B43_PHY_N(0x0EF) /*                              */
#define B43_NPHY_A1RADAR_FIFOCTL		B43_PHY_N(0x0F0) /*                              */
#define B43_NPHY_A0RADAR_FIFODAT		B43_PHY_N(0x0F1) /*                           */
#define B43_NPHY_A1RADAR_FIFODAT		B43_PHY_N(0x0F2) /*                           */
#define B43_NPHY_RADAR_THRES0			B43_PHY_N(0x0F3) /*                   */
#define B43_NPHY_RADAR_THRES1			B43_PHY_N(0x0F4) /*                   */
#define B43_NPHY_RADAR_THRES0R			B43_PHY_N(0x0F5) /*                    */
#define B43_NPHY_RADAR_THRES1R			B43_PHY_N(0x0F6) /*                    */
#define B43_NPHY_CSEN_20IN40_DLEN		B43_PHY_N(0x0F7) /*                                     */
#define B43_NPHY_RFCTL_LUT_TRSW_LO1		B43_PHY_N(0x0F8) /*                             */
#define B43_NPHY_RFCTL_LUT_TRSW_UP1		B43_PHY_N(0x0F9) /*                             */
#define B43_NPHY_RFCTL_LUT_TRSW_LO2		B43_PHY_N(0x0FA) /*                             */
#define B43_NPHY_RFCTL_LUT_TRSW_UP2		B43_PHY_N(0x0FB) /*                             */
#define B43_NPHY_RFCTL_LUT_TRSW_LO3		B43_PHY_N(0x0FC) /*                             */
#define B43_NPHY_RFCTL_LUT_TRSW_UP3		B43_PHY_N(0x0FD) /*                             */
#define B43_NPHY_RFCTL_LUT_TRSW_LO4		B43_PHY_N(0x0FE) /*                             */
#define B43_NPHY_RFCTL_LUT_TRSW_UP4		B43_PHY_N(0x0FF) /*                             */
#define B43_NPHY_RFCTL_LUT_LNAPA1		B43_PHY_N(0x100) /*                         */
#define B43_NPHY_RFCTL_LUT_LNAPA2		B43_PHY_N(0x101) /*                         */
#define B43_NPHY_RFCTL_LUT_LNAPA3		B43_PHY_N(0x102) /*                         */
#define B43_NPHY_RFCTL_LUT_LNAPA4		B43_PHY_N(0x103) /*                         */
#define B43_NPHY_TGNSYNC_CRCM0			B43_PHY_N(0x104) /*                    */
#define B43_NPHY_TGNSYNC_CRCM1			B43_PHY_N(0x105) /*                    */
#define B43_NPHY_TGNSYNC_CRCM2			B43_PHY_N(0x106) /*                    */
#define B43_NPHY_TGNSYNC_CRCM3			B43_PHY_N(0x107) /*                    */
#define B43_NPHY_TGNSYNC_CRCM4			B43_PHY_N(0x108) /*                    */
#define B43_NPHY_CRCPOLY			B43_PHY_N(0x109) /*                */
#define B43_NPHY_SIGCNT				B43_PHY_N(0x10A) /*             */
#define B43_NPHY_SIGSTARTBIT_CTL		B43_PHY_N(0x10B) /*                       */
#define B43_NPHY_CRCPOLY_ORDER			B43_PHY_N(0x10C) /*                      */
#define B43_NPHY_RFCTL_CST0			B43_PHY_N(0x10D) /*                              */
#define B43_NPHY_RFCTL_CST1			B43_PHY_N(0x10E) /*                              */
#define B43_NPHY_RFCTL_CST2O			B43_PHY_N(0x10F) /*                                       */
#define B43_NPHY_BPHY_CTL5			B43_PHY_N(0x111) /*                 */
#define B43_NPHY_RFSEQ_LPFBW			B43_PHY_N(0x112) /*                      */
#define B43_NPHY_TSSIBIAS1			B43_PHY_N(0x114) /*                 */
#define B43_NPHY_TSSIBIAS2			B43_PHY_N(0x115) /*                 */
#define  B43_NPHY_TSSIBIAS_BIAS			0x00FF /*      */
#define  B43_NPHY_TSSIBIAS_BIAS_SHIFT		0
#define  B43_NPHY_TSSIBIAS_VAL			0xFF00 /*       */
#define  B43_NPHY_TSSIBIAS_VAL_SHIFT		8
#define B43_NPHY_ESTPWR1			B43_PHY_N(0x118) /*                   */
#define B43_NPHY_ESTPWR2			B43_PHY_N(0x119) /*                   */
#define  B43_NPHY_ESTPWR_PWR			0x00FF /*                 */
#define  B43_NPHY_ESTPWR_PWR_SHIFT		0
#define  B43_NPHY_ESTPWR_VALID			0x0100 /*                       */
#define B43_NPHY_TSSI_MAXTXFDT			B43_PHY_N(0x11C) /*                              */
#define  B43_NPHY_TSSI_MAXTXFDT_VAL		0x00FF /*                         */
#define  B43_NPHY_TSSI_MAXTXFDT_VAL_SHIFT	0
#define B43_NPHY_TSSI_MAXTDT			B43_PHY_N(0x11D) /*                          */
#define  B43_NPHY_TSSI_MAXTDT_VAL		0x00FF /*                     */
#define  B43_NPHY_TSSI_MAXTDT_VAL_SHIFT		0
#define B43_NPHY_ITSSI1				B43_PHY_N(0x11E) /*             */
#define B43_NPHY_ITSSI2				B43_PHY_N(0x11F) /*             */
#define  B43_NPHY_ITSSI_VAL			0x00FF /*           */
#define  B43_NPHY_ITSSI_VAL_SHIFT		0
#define B43_NPHY_TSSIMODE			B43_PHY_N(0x122) /*           */
#define  B43_NPHY_TSSIMODE_EN			0x0001 /*             */
#define  B43_NPHY_TSSIMODE_PDEN			0x0002 /*                  */
#define B43_NPHY_RXMACIFM			B43_PHY_N(0x123) /*               */
#define B43_NPHY_CRSIT_COCNT_LO			B43_PHY_N(0x124) /*                                  */
#define B43_NPHY_CRSIT_COCNT_HI			B43_PHY_N(0x125) /*                                   */
#define B43_NPHY_CRSIT_MTCNT_LO			B43_PHY_N(0x126) /*                                        */
#define B43_NPHY_CRSIT_MTCNT_HI			B43_PHY_N(0x127) /*                                         */
#define B43_NPHY_SAMTWC				B43_PHY_N(0x128) /*                        */
#define B43_NPHY_IQEST_CMD			B43_PHY_N(0x129) /*                      */
#define  B43_NPHY_IQEST_CMD_START		0x0001 /*       */
#define  B43_NPHY_IQEST_CMD_MODE		0x0002 /*      */
#define B43_NPHY_IQEST_WT			B43_PHY_N(0x12A) /*                        */
#define  B43_NPHY_IQEST_WT_VAL			0x00FF /*           */
#define  B43_NPHY_IQEST_WT_VAL_SHIFT		0
#define B43_NPHY_IQEST_SAMCNT			B43_PHY_N(0x12B) /*                           */
#define B43_NPHY_IQEST_IQACC_LO0		B43_PHY_N(0x12C) /*                           */
#define B43_NPHY_IQEST_IQACC_HI0		B43_PHY_N(0x12D) /*                           */
#define B43_NPHY_IQEST_IPACC_LO0		B43_PHY_N(0x12E) /*                               */
#define B43_NPHY_IQEST_IPACC_HI0		B43_PHY_N(0x12F) /*                               */
#define B43_NPHY_IQEST_QPACC_LO0		B43_PHY_N(0x130) /*                               */
#define B43_NPHY_IQEST_QPACC_HI0		B43_PHY_N(0x131) /*                               */
#define B43_NPHY_IQEST_IQACC_LO1		B43_PHY_N(0x134) /*                           */
#define B43_NPHY_IQEST_IQACC_HI1		B43_PHY_N(0x135) /*                           */
#define B43_NPHY_IQEST_IPACC_LO1		B43_PHY_N(0x136) /*                               */
#define B43_NPHY_IQEST_IPACC_HI1		B43_PHY_N(0x137) /*                               */
#define B43_NPHY_IQEST_QPACC_LO1		B43_PHY_N(0x138) /*                               */
#define B43_NPHY_IQEST_QPACC_HI1		B43_PHY_N(0x139) /*                               */
#define B43_NPHY_MIMO_CRSTXEXT			B43_PHY_N(0x13A) /*                           */
#define B43_NPHY_PWRDET1			B43_PHY_N(0x13B) /*             */
#define B43_NPHY_PWRDET2			B43_PHY_N(0x13C) /*             */
#define B43_NPHY_MAXRSSI_DTIME			B43_PHY_N(0x13F) /*                          */
#define B43_NPHY_PIL_DW0			B43_PHY_N(0x141) /*                     */
#define B43_NPHY_PIL_DW1			B43_PHY_N(0x142) /*                     */
#define B43_NPHY_PIL_DW2			B43_PHY_N(0x143) /*                     */
#define  B43_NPHY_PIL_DW_BPSK			0x000F /*      */
#define  B43_NPHY_PIL_DW_BPSK_SHIFT		0
#define  B43_NPHY_PIL_DW_QPSK			0x00F0 /*      */
#define  B43_NPHY_PIL_DW_QPSK_SHIFT		4
#define  B43_NPHY_PIL_DW_16QAM			0x0F00 /*        */
#define  B43_NPHY_PIL_DW_16QAM_SHIFT		8
#define  B43_NPHY_PIL_DW_64QAM			0xF000 /*        */
#define  B43_NPHY_PIL_DW_64QAM_SHIFT		12
#define B43_NPHY_FMDEM_CFG			B43_PHY_N(0x144) /*                        */
#define B43_NPHY_PHASETR_A0			B43_PHY_N(0x145) /*                     */
#define B43_NPHY_PHASETR_A1			B43_PHY_N(0x146) /*                     */
#define B43_NPHY_PHASETR_A2			B43_PHY_N(0x147) /*                     */
#define B43_NPHY_PHASETR_B0			B43_PHY_N(0x148) /*                    */
#define B43_NPHY_PHASETR_B1			B43_PHY_N(0x149) /*                    */
#define B43_NPHY_PHASETR_B2			B43_PHY_N(0x14A) /*                    */
#define B43_NPHY_PHASETR_CHG0			B43_PHY_N(0x14B) /*                      */
#define B43_NPHY_PHASETR_CHG1			B43_PHY_N(0x14C) /*                      */
#define B43_NPHY_PHASETW_OFF			B43_PHY_N(0x14D) /*                    */
#define B43_NPHY_RFCTL_DBG			B43_PHY_N(0x14E) /*                  */
#define B43_NPHY_CCK_SHIFTB_REF			B43_PHY_N(0x150) /*                             */
#define B43_NPHY_OVER_DGAIN0			B43_PHY_N(0x152) /*                         */
#define B43_NPHY_OVER_DGAIN1			B43_PHY_N(0x153) /*                         */
#define  B43_NPHY_OVER_DGAIN_FDGV		0x0007 /*                          */
#define  B43_NPHY_OVER_DGAIN_FDGV_SHIFT		0
#define  B43_NPHY_OVER_DGAIN_FDGEN		0x0008 /*                           */
#define  B43_NPHY_OVER_DGAIN_CCKDGECV		0xFF00 /*                                     */
#define  B43_NPHY_OVER_DGAIN_CCKDGECV_SHIFT	8
#define B43_NPHY_BIST_STAT4			B43_PHY_N(0x156) /*               */
#define B43_NPHY_RADAR_MAL			B43_PHY_N(0x157) /*                 */
#define B43_NPHY_RADAR_SRCCTL			B43_PHY_N(0x158) /*                      */
#define B43_NPHY_VLD_DTSIG			B43_PHY_N(0x159) /*                    */
#define B43_NPHY_VLD_DTDAT			B43_PHY_N(0x15A) /*                     */
#define B43_NPHY_C1_BPHY_RXIQCA0		B43_PHY_N(0x15B) /*                             */
#define B43_NPHY_C1_BPHY_RXIQCB0		B43_PHY_N(0x15C) /*                             */
#define B43_NPHY_C2_BPHY_RXIQCA1		B43_PHY_N(0x15D) /*                             */
#define B43_NPHY_C2_BPHY_RXIQCB1		B43_PHY_N(0x15E) /*                             */
#define B43_NPHY_FREQGAIN0			B43_PHY_N(0x160) /*                  */
#define B43_NPHY_FREQGAIN1			B43_PHY_N(0x161) /*                  */
#define B43_NPHY_FREQGAIN2			B43_PHY_N(0x162) /*                  */
#define B43_NPHY_FREQGAIN3			B43_PHY_N(0x163) /*                  */
#define B43_NPHY_FREQGAIN4			B43_PHY_N(0x164) /*                  */
#define B43_NPHY_FREQGAIN5			B43_PHY_N(0x165) /*                  */
#define B43_NPHY_FREQGAIN6			B43_PHY_N(0x166) /*                  */
#define B43_NPHY_FREQGAIN7			B43_PHY_N(0x167) /*                  */
#define B43_NPHY_FREQGAIN_BYPASS		B43_PHY_N(0x168) /*                       */
#define B43_NPHY_TRLOSS				B43_PHY_N(0x169) /*               */
#define B43_NPHY_C1_ADCCLIP			B43_PHY_N(0x16A) /*                 */
#define B43_NPHY_C2_ADCCLIP			B43_PHY_N(0x16B) /*                 */
#define B43_NPHY_LTRN_OFFGAIN			B43_PHY_N(0x16F) /*                  */
#define B43_NPHY_LTRN_OFF			B43_PHY_N(0x170) /*             */
#define B43_NPHY_NRDATAT_WWISE20SIG		B43_PHY_N(0x171) /*                           */
#define B43_NPHY_NRDATAT_WWISE40SIG		B43_PHY_N(0x172) /*                           */
#define B43_NPHY_NRDATAT_TGNSYNC20SIG		B43_PHY_N(0x173) /*                             */
#define B43_NPHY_NRDATAT_TGNSYNC40SIG		B43_PHY_N(0x174) /*                             */
#define B43_NPHY_WWISE_CRCM0			B43_PHY_N(0x175) /*                  */
#define B43_NPHY_WWISE_CRCM1			B43_PHY_N(0x176) /*                  */
#define B43_NPHY_WWISE_CRCM2			B43_PHY_N(0x177) /*                  */
#define B43_NPHY_WWISE_CRCM3			B43_PHY_N(0x178) /*                  */
#define B43_NPHY_WWISE_CRCM4			B43_PHY_N(0x179) /*                  */
#define B43_NPHY_CHANEST_CDDSH			B43_PHY_N(0x17A) /*                            */
#define B43_NPHY_HTAGC_WCNT			B43_PHY_N(0x17B) /*                      */
#define B43_NPHY_SQPARM				B43_PHY_N(0x17C) /*           */
#define B43_NPHY_MCSDUP6M			B43_PHY_N(0x17D) /*            */
#define B43_NPHY_NDATAT_DUP40			B43_PHY_N(0x17E) /*                     */
#define B43_NPHY_DUP40_TGNSYNC_CYCD		B43_PHY_N(0x17F) /*                          */
#define B43_NPHY_DUP40_GFBL			B43_PHY_N(0x180) /*                            */
#define B43_NPHY_DUP40_BL			B43_PHY_N(0x181) /*                         */
#define B43_NPHY_LEGDUP_FTA			B43_PHY_N(0x182) /*                              */
#define B43_NPHY_PACPROC_DBG			B43_PHY_N(0x183) /*                         */
#define B43_NPHY_PIL_CYC1			B43_PHY_N(0x184) /*                       */
#define B43_NPHY_PIL_CYC2			B43_PHY_N(0x185) /*                       */
#define B43_NPHY_TXF_20CO_S0A1			B43_PHY_N(0x186) /*                               */
#define B43_NPHY_TXF_20CO_S0A2			B43_PHY_N(0x187) /*                               */
#define B43_NPHY_TXF_20CO_S1A1			B43_PHY_N(0x188) /*                               */
#define B43_NPHY_TXF_20CO_S1A2			B43_PHY_N(0x189) /*                               */
#define B43_NPHY_TXF_20CO_S2A1			B43_PHY_N(0x18A) /*                               */
#define B43_NPHY_TXF_20CO_S2A2			B43_PHY_N(0x18B) /*                               */
#define B43_NPHY_TXF_20CO_S0B1			B43_PHY_N(0x18C) /*                               */
#define B43_NPHY_TXF_20CO_S0B2			B43_PHY_N(0x18D) /*                               */
#define B43_NPHY_TXF_20CO_S0B3			B43_PHY_N(0x18E) /*                               */
#define B43_NPHY_TXF_20CO_S1B1			B43_PHY_N(0x18F) /*                               */
#define B43_NPHY_TXF_20CO_S1B2			B43_PHY_N(0x190) /*                               */
#define B43_NPHY_TXF_20CO_S1B3			B43_PHY_N(0x191) /*                               */
#define B43_NPHY_TXF_20CO_S2B1			B43_PHY_N(0x192) /*                               */
#define B43_NPHY_TXF_20CO_S2B2			B43_PHY_N(0x193) /*                               */
#define B43_NPHY_TXF_20CO_S2B3			B43_PHY_N(0x194) /*                               */
#define B43_NPHY_TXF_40CO_S0A1			B43_PHY_N(0x195) /*                               */
#define B43_NPHY_TXF_40CO_S0A2			B43_PHY_N(0x196) /*                               */
#define B43_NPHY_TXF_40CO_S1A1			B43_PHY_N(0x197) /*                               */
#define B43_NPHY_TXF_40CO_S1A2			B43_PHY_N(0x198) /*                               */
#define B43_NPHY_TXF_40CO_S2A1			B43_PHY_N(0x199) /*                               */
#define B43_NPHY_TXF_40CO_S2A2			B43_PHY_N(0x19A) /*                               */
#define B43_NPHY_TXF_40CO_S0B1			B43_PHY_N(0x19B) /*                               */
#define B43_NPHY_TXF_40CO_S0B2			B43_PHY_N(0x19C) /*                               */
#define B43_NPHY_TXF_40CO_S0B3			B43_PHY_N(0x19D) /*                               */
#define B43_NPHY_TXF_40CO_S1B1			B43_PHY_N(0x19E) /*                               */
#define B43_NPHY_TXF_40CO_S1B2			B43_PHY_N(0x19F) /*                               */
#define B43_NPHY_TXF_40CO_S1B3			B43_PHY_N(0x1A0) /*                               */
#define B43_NPHY_TXF_40CO_S2B1			B43_PHY_N(0x1A1) /*                               */
#define B43_NPHY_TXF_40CO_S2B2			B43_PHY_N(0x1A2) /*                               */
#define B43_NPHY_TXF_40CO_S2B3			B43_PHY_N(0x1A3) /*                               */
#define B43_NPHY_RSSIMC_0I_RSSI_X		B43_PHY_N(0x1A4) /*                                            */
#define B43_NPHY_RSSIMC_0I_RSSI_Y		B43_PHY_N(0x1A5) /*                                            */
#define B43_NPHY_RSSIMC_0I_RSSI_Z		B43_PHY_N(0x1A6) /*                                            */
#define B43_NPHY_RSSIMC_0I_TBD			B43_PHY_N(0x1A7) /*                                         */
#define B43_NPHY_RSSIMC_0I_PWRDET		B43_PHY_N(0x1A8) /*                                               */
#define B43_NPHY_RSSIMC_0I_TSSI			B43_PHY_N(0x1A9) /*                                          */
#define B43_NPHY_RSSIMC_0Q_RSSI_X		B43_PHY_N(0x1AA) /*                                            */
#define B43_NPHY_RSSIMC_0Q_RSSI_Y		B43_PHY_N(0x1AB) /*                                            */
#define B43_NPHY_RSSIMC_0Q_RSSI_Z		B43_PHY_N(0x1AC) /*                                            */
#define B43_NPHY_RSSIMC_0Q_TBD			B43_PHY_N(0x1AD) /*                                         */
#define B43_NPHY_RSSIMC_0Q_PWRDET		B43_PHY_N(0x1AE) /*                                               */
#define B43_NPHY_RSSIMC_0Q_TSSI			B43_PHY_N(0x1AF) /*                                          */
#define B43_NPHY_RSSIMC_1I_RSSI_X		B43_PHY_N(0x1B0) /*                                            */
#define B43_NPHY_RSSIMC_1I_RSSI_Y		B43_PHY_N(0x1B1) /*                                            */
#define B43_NPHY_RSSIMC_1I_RSSI_Z		B43_PHY_N(0x1B2) /*                                            */
#define B43_NPHY_RSSIMC_1I_TBD			B43_PHY_N(0x1B3) /*                                         */
#define B43_NPHY_RSSIMC_1I_PWRDET		B43_PHY_N(0x1B4) /*                                               */
#define B43_NPHY_RSSIMC_1I_TSSI			B43_PHY_N(0x1B5) /*                                          */
#define B43_NPHY_RSSIMC_1Q_RSSI_X		B43_PHY_N(0x1B6) /*                                            */
#define B43_NPHY_RSSIMC_1Q_RSSI_Y		B43_PHY_N(0x1B7) /*                                            */
#define B43_NPHY_RSSIMC_1Q_RSSI_Z		B43_PHY_N(0x1B8) /*                                            */
#define B43_NPHY_RSSIMC_1Q_TBD			B43_PHY_N(0x1B9) /*                                         */
#define B43_NPHY_RSSIMC_1Q_PWRDET		B43_PHY_N(0x1BA) /*                                               */
#define B43_NPHY_RSSIMC_1Q_TSSI			B43_PHY_N(0x1BB) /*                                          */
#define B43_NPHY_SAMC_WCNT			B43_PHY_N(0x1BC) /*                             */
#define B43_NPHY_PTHROUGH_CNT			B43_PHY_N(0x1BD) /*                      */
#define B43_NPHY_LTRN_OFF_G20L			B43_PHY_N(0x1C4) /*                      */
#define B43_NPHY_LTRN_OFF_20L			B43_PHY_N(0x1C5) /*                 */
#define B43_NPHY_LTRN_OFF_G20U			B43_PHY_N(0x1C6) /*                      */
#define B43_NPHY_LTRN_OFF_20U			B43_PHY_N(0x1C7) /*                 */
#define B43_NPHY_DSSSCCK_GAINSL			B43_PHY_N(0x1C8) /*                             */
#define B43_NPHY_GPIO_LOOUT			B43_PHY_N(0x1C9) /*              */
#define B43_NPHY_GPIO_HIOUT			B43_PHY_N(0x1CA) /*               */
#define B43_NPHY_CRS_CHECK			B43_PHY_N(0x1CB) /*           */
#define B43_NPHY_ML_LOGSS_RAT			B43_PHY_N(0x1CC) /*                */
#define B43_NPHY_DUPSCALE			B43_PHY_N(0x1CD) /*           */
#define B43_NPHY_BW1A				B43_PHY_N(0x1CE) /*       */
#define B43_NPHY_BW2				B43_PHY_N(0x1CF) /*      */
#define B43_NPHY_BW3				B43_PHY_N(0x1D0) /*      */
#define B43_NPHY_BW4				B43_PHY_N(0x1D1) /*      */
#define B43_NPHY_BW5				B43_PHY_N(0x1D2) /*      */
#define B43_NPHY_BW6				B43_PHY_N(0x1D3) /*      */
#define B43_NPHY_COALEN0			B43_PHY_N(0x1D4) /*                 */
#define B43_NPHY_COALEN1			B43_PHY_N(0x1D5) /*                 */
#define B43_NPHY_CRSTHRES_1U			B43_PHY_N(0x1D6) /*                   */
#define B43_NPHY_CRSTHRES_2U			B43_PHY_N(0x1D7) /*                   */
#define B43_NPHY_CRSTHRES_3U			B43_PHY_N(0x1D8) /*                   */
#define B43_NPHY_CRSCTL_U			B43_PHY_N(0x1D9) /*               */
#define B43_NPHY_CRSTHRES_1L			B43_PHY_N(0x1DA) /*                   */
#define B43_NPHY_CRSTHRES_2L			B43_PHY_N(0x1DB) /*                   */
#define B43_NPHY_CRSTHRES_3L			B43_PHY_N(0x1DC) /*                   */
#define B43_NPHY_CRSCTL_L			B43_PHY_N(0x1DD) /*               */
#define B43_NPHY_STRA_1U			B43_PHY_N(0x1DE) /*                 */
#define B43_NPHY_STRA_2U			B43_PHY_N(0x1DF) /*                 */
#define B43_NPHY_STRA_1L			B43_PHY_N(0x1E0) /*                 */
#define B43_NPHY_STRA_2L			B43_PHY_N(0x1E1) /*                 */
#define B43_NPHY_CRSCHECK1			B43_PHY_N(0x1E2) /*             */
#define B43_NPHY_CRSCHECK2			B43_PHY_N(0x1E3) /*             */
#define B43_NPHY_CRSCHECK3			B43_PHY_N(0x1E4) /*             */
#define B43_NPHY_JMPSTP0			B43_PHY_N(0x1E5) /*             */
#define B43_NPHY_JMPSTP1			B43_PHY_N(0x1E6) /*             */
#define B43_NPHY_TXPCTL_CMD			B43_PHY_N(0x1E7) /*                          */
#define  B43_NPHY_TXPCTL_CMD_INIT		0x007F /*      */
#define  B43_NPHY_TXPCTL_CMD_INIT_SHIFT		0
#define  B43_NPHY_TXPCTL_CMD_COEFF		0x2000 /*                            */
#define  B43_NPHY_TXPCTL_CMD_HWPCTLEN		0x4000 /*                                  */
#define  B43_NPHY_TXPCTL_CMD_PCTLEN		0x8000 /*                         */
#define B43_NPHY_TXPCTL_N			B43_PHY_N(0x1E8) /*                        */
#define  B43_NPHY_TXPCTL_N_TSSID		0x00FF /*              */
#define  B43_NPHY_TXPCTL_N_TSSID_SHIFT		0
#define  B43_NPHY_TXPCTL_N_NPTIL2		0x0700 /*                   */
#define  B43_NPHY_TXPCTL_N_NPTIL2_SHIFT		8
#define B43_NPHY_TXPCTL_ITSSI			B43_PHY_N(0x1E9) /*                            */
#define  B43_NPHY_TXPCTL_ITSSI_0		0x003F /*             */
#define  B43_NPHY_TXPCTL_ITSSI_0_SHIFT		0
#define  B43_NPHY_TXPCTL_ITSSI_1		0x3F00 /*             */
#define  B43_NPHY_TXPCTL_ITSSI_1_SHIFT		8
#define  B43_NPHY_TXPCTL_ITSSI_BINF		0x8000 /*                            */
#define B43_NPHY_TXPCTL_TPWR			B43_PHY_N(0x1EA) /*                               */
#define  B43_NPHY_TXPCTL_TPWR_0			0x00FF /*         */
#define  B43_NPHY_TXPCTL_TPWR_0_SHIFT		0
#define  B43_NPHY_TXPCTL_TPWR_1			0xFF00 /*         */
#define  B43_NPHY_TXPCTL_TPWR_1_SHIFT		8
#define B43_NPHY_TXPCTL_BIDX			B43_PHY_N(0x1EB) /*                             */
#define  B43_NPHY_TXPCTL_BIDX_0			0x007F /*                 */
#define  B43_NPHY_TXPCTL_BIDX_0_SHIFT		0
#define  B43_NPHY_TXPCTL_BIDX_1			0x7F00 /*                 */
#define  B43_NPHY_TXPCTL_BIDX_1_SHIFT		8
#define  B43_NPHY_TXPCTL_BIDX_LOAD		0x8000 /*                 */
#define B43_NPHY_TXPCTL_PIDX			B43_PHY_N(0x1EC) /*                              */
#define  B43_NPHY_TXPCTL_PIDX_0			0x007F /*                  */
#define  B43_NPHY_TXPCTL_PIDX_0_SHIFT		0
#define  B43_NPHY_TXPCTL_PIDX_1			0x7F00 /*                  */
#define  B43_NPHY_TXPCTL_PIDX_1_SHIFT		8
#define B43_NPHY_C1_TXPCTL_STAT			B43_PHY_N(0x1ED) /*                                */
#define B43_NPHY_C2_TXPCTL_STAT			B43_PHY_N(0x1EE) /*                                */
#define  B43_NPHY_TXPCTL_STAT_EST		0x00FF /*                 */
#define  B43_NPHY_TXPCTL_STAT_EST_SHIFT		0
#define  B43_NPHY_TXPCTL_STAT_BIDX		0x7F00 /*            */
#define  B43_NPHY_TXPCTL_STAT_BIDX_SHIFT	8
#define  B43_NPHY_TXPCTL_STAT_ESTVALID		0x8000 /*                       */
#define B43_NPHY_SMALLSGS_LEN			B43_PHY_N(0x1EF) /*                              */
#define B43_NPHY_PHYSTAT_GAIN0			B43_PHY_N(0x1F0) /*                       */
#define B43_NPHY_PHYSTAT_GAIN1			B43_PHY_N(0x1F1) /*                       */
#define B43_NPHY_PHYSTAT_FREQEST		B43_PHY_N(0x1F2) /*                              */
#define B43_NPHY_PHYSTAT_ADVRET			B43_PHY_N(0x1F3) /*                      */
#define B43_NPHY_PHYLB_MODE			B43_PHY_N(0x1F4) /*                   */
#define B43_NPHY_TONE_MIDX20_1			B43_PHY_N(0x1F5) /*                     */
#define B43_NPHY_TONE_MIDX20_2			B43_PHY_N(0x1F6) /*                     */
#define B43_NPHY_TONE_MIDX20_3			B43_PHY_N(0x1F7) /*                     */
#define B43_NPHY_TONE_MIDX40_1			B43_PHY_N(0x1F8) /*                     */
#define B43_NPHY_TONE_MIDX40_2			B43_PHY_N(0x1F9) /*                     */
#define B43_NPHY_TONE_MIDX40_3			B43_PHY_N(0x1FA) /*                     */
#define B43_NPHY_TONE_MIDX40_4			B43_PHY_N(0x1FB) /*                     */
#define B43_NPHY_PILTONE_MIDX1			B43_PHY_N(0x1FC) /*                        */
#define B43_NPHY_PILTONE_MIDX2			B43_PHY_N(0x1FD) /*                        */
#define B43_NPHY_PILTONE_MIDX3			B43_PHY_N(0x1FE) /*                        */
#define B43_NPHY_TXRIFS_FRDEL			B43_PHY_N(0x1FF) /*                     */
#define B43_NPHY_AFESEQ_RX2TX_PUD_40M		B43_PHY_N(0x200) /*                                       */
#define B43_NPHY_AFESEQ_TX2RX_PUD_40M		B43_PHY_N(0x201) /*                                       */
#define B43_NPHY_AFESEQ_RX2TX_PUD_20M		B43_PHY_N(0x202) /*                                       */
#define B43_NPHY_AFESEQ_TX2RX_PUD_20M		B43_PHY_N(0x203) /*                                       */
#define B43_NPHY_RX_SIGCTL			B43_PHY_N(0x204) /*                   */
#define B43_NPHY_RXPIL_CYCNT0			B43_PHY_N(0x205) /*                          */
#define B43_NPHY_RXPIL_CYCNT1			B43_PHY_N(0x206) /*                          */
#define B43_NPHY_RXPIL_CYCNT2			B43_PHY_N(0x207) /*                          */
#define B43_NPHY_AFESEQ_RX2TX_PUD_10M		B43_PHY_N(0x208) /*                                       */
#define B43_NPHY_AFESEQ_TX2RX_PUD_10M		B43_PHY_N(0x209) /*                                       */
#define B43_NPHY_DSSSCCK_CRSEXTL		B43_PHY_N(0x20A) /*                               */
#define B43_NPHY_ML_LOGSS_RATSLOPE		B43_PHY_N(0x20B) /*                      */
#define B43_NPHY_RIFS_SRCTL			B43_PHY_N(0x20C) /*                            */
#define B43_NPHY_TXREALFD			B43_PHY_N(0x20D) /*                     */
#define B43_NPHY_HPANT_SWTHRES			B43_PHY_N(0x20E) /*                                     */
#define B43_NPHY_EDCRS_ASSTHRES0		B43_PHY_N(0x210) /*                           */
#define B43_NPHY_EDCRS_ASSTHRES1		B43_PHY_N(0x211) /*                           */
#define B43_NPHY_EDCRS_DEASSTHRES0		B43_PHY_N(0x212) /*                             */
#define B43_NPHY_EDCRS_DEASSTHRES1		B43_PHY_N(0x213) /*                             */
#define B43_NPHY_STR_WTIME20U			B43_PHY_N(0x214) /*                   */
#define B43_NPHY_STR_WTIME20L			B43_PHY_N(0x215) /*                   */
#define B43_NPHY_TONE_MIDX657M			B43_PHY_N(0x216) /*                     */
#define B43_NPHY_HTSIGTONES			B43_PHY_N(0x217) /*                 */
#define B43_NPHY_RSSI1				B43_PHY_N(0x219) /*              */
#define B43_NPHY_RSSI2				B43_PHY_N(0x21A) /*              */
#define B43_NPHY_CHAN_ESTHANG			B43_PHY_N(0x21D) /*                       */
#define B43_NPHY_FINERX2_CGC			B43_PHY_N(0x221) /*                              */
#define  B43_NPHY_FINERX2_CGC_DECGC		0x0008 /*                     */
#define B43_NPHY_TXPCTL_INIT			B43_PHY_N(0x222) /*                       */
#define  B43_NPHY_TXPCTL_INIT_PIDXI1		0x00FF /*                    */
#define  B43_NPHY_TXPCTL_INIT_PIDXI1_SHIFT	0
#define B43_NPHY_PAPD_EN0			B43_PHY_N(0x297) /*                  */
#define B43_NPHY_EPS_TABLE_ADJ0			B43_PHY_N(0x298) /*                    */
#define B43_NPHY_PAPD_EN1			B43_PHY_N(0x29B) /*                  */
#define B43_NPHY_EPS_TABLE_ADJ1			B43_PHY_N(0x29C) /*                    */

#define B43_PHY_B_BBCFG				B43_PHY_N_BMODE(0x001) /*           */
#define B43_PHY_B_TEST				B43_PHY_N_BMODE(0x00A)

struct b43_wldev;

enum b43_nphy_spur_avoid {
	B43_SPUR_AVOID_DISABLE,
	B43_SPUR_AVOID_AUTO,
	B43_SPUR_AVOID_FORCE,
};

struct b43_chanspec {
	u16 center_freq;
	enum nl80211_channel_type channel_type;
};

struct b43_phy_n_iq_comp {
	s16 a0;
	s16 b0;
	s16 a1;
	s16 b1;
};

struct b43_phy_n_rssical_cache {
	u16 rssical_radio_regs_2G[2];
	u16 rssical_phy_regs_2G[12];

	u16 rssical_radio_regs_5G[2];
	u16 rssical_phy_regs_5G[12];
};

struct b43_phy_n_cal_cache {
	u16 txcal_radio_regs_2G[8];
	u16 txcal_coeffs_2G[8];
	struct b43_phy_n_iq_comp rxcal_coeffs_2G;

	u16 txcal_radio_regs_5G[8];
	u16 txcal_coeffs_5G[8];
	struct b43_phy_n_iq_comp rxcal_coeffs_5G;
};

struct b43_phy_n_txpwrindex {
	s8 index;
	s8 index_internal;
	s8 index_internal_save;
	u16 AfectrlOverride;
	u16 AfeCtrlDacGain;
	u16 rad_gain;
	u8 bbmult;
	u16 iqcomp_a;
	u16 iqcomp_b;
	u16 locomp;
};

struct b43_phy_n_pwr_ctl_info {
	u8 idle_tssi_2g;
	u8 idle_tssi_5g;
};

struct b43_phy_n {
	u8 antsel_type;
	u8 cal_orig_pwr_idx[2];
	u8 measure_hold;
	u8 phyrxchain;
	u8 hw_phyrxchain;
	u8 hw_phytxchain;
	u8 perical;
	u32 deaf_count;
	u32 rxcalparams;
	bool hang_avoid;
	bool mute;
	u16 papd_epsilon_offset[2];
	s32 preamble_override;
	u32 bb_mult_save;

	bool gain_boost;
	bool elna_gain_config;
	bool band5g_pwrgain;

	u8 mphase_cal_phase_id;
	u16 mphase_txcal_cmdidx;
	u16 mphase_txcal_numcmds;
	u16 mphase_txcal_bestcoeffs[11];

	bool txpwrctrl;
	bool pwg_gain_5ghz;
	u8 tx_pwr_idx[2];
	s8 tx_power_offset[101];
	u16 adj_pwr_tbl[84];
	u16 txcal_bbmult;
	u16 txiqlocal_bestc[11];
	bool txiqlocal_coeffsvalid;
	struct b43_phy_n_txpwrindex txpwrindex[2];
	struct b43_phy_n_pwr_ctl_info pwr_ctl_info[2];
	struct b43_chanspec txiqlocal_chanspec;

	u8 txrx_chain;
	u16 tx_rx_cal_phy_saveregs[11];
	u16 tx_rx_cal_radio_saveregs[22];

	u16 rfctrl_intc1_save;
	u16 rfctrl_intc2_save;

	u16 classifier_state;
	u16 clip_state[2];

	enum b43_nphy_spur_avoid spur_avoid;
	bool aband_spurwar_en;
	bool gband_spurwar_en;

	bool ipa2g_on;
	struct b43_chanspec iqcal_chanspec_2G;
	struct b43_chanspec rssical_chanspec_2G;

	bool ipa5g_on;
	struct b43_chanspec iqcal_chanspec_5G;
	struct b43_chanspec rssical_chanspec_5G;

	struct b43_phy_n_rssical_cache rssical_cache;
	struct b43_phy_n_cal_cache cal_cache;
	bool crsminpwr_adjusted;
	bool noisevars_adjusted;
};


struct b43_phy_operations;
extern const struct b43_phy_operations b43_phyops_n;

#endif /*             */
