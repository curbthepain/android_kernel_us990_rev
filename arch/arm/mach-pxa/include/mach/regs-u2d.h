#ifndef __ASM_ARCH_PXA3xx_U2D_H
#define __ASM_ARCH_PXA3xx_U2D_H

#include <mach/bitfield.h>

/*
                                                        
 */
#define U2DCR		(0x0000)	/*                      */
#define U2DCR_NDC	(1   << 31)	/*                   */
#define U2DCR_HSTC	(0x7 << 28)	/*                                */
#define U2DCR_SPEOREN	(1   << 27)	/*                                         */
#define U2DCR_FSTC	(0x7 << 24)	/*                                */
#define U2DCR_UCLKOVR	(1   << 22)	/*                    */
#define U2DCR_ABP	(1   << 21)	/*                       */
#define U2DCR_ADD	(1   << 20)	/*                               */
#define U2DCR_CC	(1   << 19)	/*                      */
#define U2DCR_HS	(1   << 18)	/*                          */
#define U2DCR_SMAC	(1   << 17)	/*                                                */
#define U2DCR_DWRE	(1   << 16)	/*                               */
#define U2DCR_ACN	(0xf << 12)	/*                                 */
#define U2DCR_AIN	(0xf << 8)	/*                             */
#define U2DCR_AAISN	(0xf << 4)	/*                                               */
#define U2DCR_EMCE	(1   << 3)	/*                                     */
#define U2DCR_UDR	(1   << 2)	/*            */
#define U2DCR_UDA	(1   << 1)	/*            */
#define U2DCR_UDE	(1   << 0)	/*            */

#define U2DICR			(0x0004)	/*                                */
#define U2DISR			(0x000C)	/*                               */
#define U2DINT_CC		(1 << 31)	/*                                  */
#define U2DINT_SOF		(1 << 30)	/*                 */
#define U2DINT_USOF		(1 << 29)	/*                       */
#define U2DINT_RU		(1 << 28)	/*                    */
#define U2DINT_SU		(1 << 27)	/*                     */
#define U2DINT_RS		(1 << 26)	/*                   */
#define U2DINT_DPE		(1 << 25)	/*                               */
#define U2DINT_FIFOERR		(0x4)		/*                                 */
#define U2DINT_PACKETCMP	(0x2)		/*                                      */
#define U2DINT_SPACKETCMP	(0x1)		/*                                            */

#define U2DFNR			(0x0014)	/*                           */

#define U2DINT(n, intr)		(((intr) & 0x07) << (((n) & 0x07) * 3))
#define U2DICR2			(0x0008)	/*                                  */
#define U2DISR2			(0x0010)	/*                                 */

#define U2DOTGCR		(0x0020)	/*                          */
#define U2DOTGCR_OTGEN		(1 << 31)	/*                  */
#define U2DOTGCR_AALTHNP	(1 << 30)	/*                                                           */
#define U2DOTGCR_AHNP		(1 << 29)	/*                                            */
#define U2DOTGCR_BHNP		(1 << 28)	/*                                           */

#ifdef CONFIG_CPU_PXA930
#define U2DOTGCR_LPA		(1 << 15)	/*                            */
#define U2DOTGCR_IESI		(1 << 13)	/*                      */
#define U2DOTGCR_ISSI		(1 << 12)	/*                      */
#endif

#define U2DOTGCR_CKAF	(1 << 5)	/*                                       */
#define U2DOTGCR_UTMID	(1 << 4)	/*                        */
#define U2DOTGCR_ULAF	(1 << 3)	/*                                     */
#define U2DOTGCR_SMAF	(1 << 2)	/*                                       */
#define U2DOTGCR_RTSM	(1 << 1)	/*                                        */
#define U2DOTGCR_ULE	(1 << 0)	/*                     */

#define U2DOTGICR	(0x0024)	/*                                    */
#define U2DOTGISR	(0x0028)	/*                                   */

#define U2DOTGINT_SF	(1 << 17)	/*                                  */
#define U2DOTGINT_SI	(1 << 16)	/*               */
#define U2DOTGINT_RLS1	(1 << 14)	/*                                          */
#define U2DOTGINT_RLS0	(1 << 13)	/*                                          */
#define U2DOTGINT_RID	(1 << 12)	/*                                    */
#define U2DOTGINT_RSE	(1 << 11)	/*                                      */
#define U2DOTGINT_RSV	(1 << 10)	/*                                        */
#define U2DOTGINT_RVV	(1 << 9)	/*                                     */
#define U2DOTGINT_RCK	(1 << 8)	/*                             */
#define U2DOTGINT_FLS1	(1 << 6)	/*                                          */
#define U2DOTGINT_FLS0	(1 << 5)	/*                                          */
#define U2DOTGINT_FID	(1 << 4)	/*                                    */
#define U2DOTGINT_FSE	(1 << 3)	/*                                      */
#define U2DOTGINT_FSV	(1 << 2)	/*                                        */
#define U2DOTGINT_FVV	(1 << 1)	/*                                     */
#define U2DOTGINT_FCK	(1 << 0)	/*                             */

#define U2DOTGUSR	(0x002C)	/*                              */
#define U2DOTGUSR_LPA	(1 << 31)	/*                            */
#define U2DOTGUSR_S6A	(1 << 30)	/*                                 */
#define U2DOTGUSR_S3A	(1 << 29)	/*                                 */
#define U2DOTGUSR_CKA	(1 << 28)	/*                          */
#define U2DOTGUSR_LS1	(1 << 6)	/*                          */
#define U2DOTGUSR_LS0	(1 << 5)	/*                          */
#define U2DOTGUSR_ID	(1 << 4)	/*                  */
#define U2DOTGUSR_SE	(1 << 3)	/*                        */
#define U2DOTGUSR_SV	(1 << 2)	/*                          */
#define U2DOTGUSR_VV	(1 << 1)	/*                       */
#define U2DOTGUSR_CK	(1 << 0)	/*                         */

#define U2DOTGUCR	(0x0030)	/*                               */
#define U2DOTGUCR_RUN	(1    << 25)	/*     */
#define U2DOTGUCR_RNW	(1    << 24)	/*                         */
#define U2DOTGUCR_ADDR	(0x3f << 16)	/*                                  */
#define U2DOTGUCR_WDATA	(0xff << 8)	/*                              */
#define U2DOTGUCR_RDATA	(0xff << 0)	/*                             */

#define U2DP3CR		(0x0034)	/*                             */
#define U2DP3CR_P2SS	(0x3 << 8)	/*                                */
#define U2DP3CR_P3SS	(0x7 << 4)	/*                                */
#define U2DP3CR_VPVMBEN	(0x1 << 2)	/*                                */
#define U2DP3CR_CFG	(0x3 << 0)	/*                           */

#define U2DCSR0		(0x0100)	/*                                          */
#define U2DCSR0_IPA	(1 << 8)	/*                    */
#define U2DCSR0_SA	(1 << 7)	/*              */
#define U2DCSR0_RNE	(1 << 6)	/*                        */
#define U2DCSR0_FST	(1 << 5)	/*             */
#define U2DCSR0_SST	(1 << 4)	/*            */
#define U2DCSR0_DME	(1 << 3)	/*            */
#define U2DCSR0_FTF	(1 << 2)	/*                     */
#define U2DCSR0_IPR	(1 << 1)	/*                 */
#define U2DCSR0_OPC	(1 << 0)	/*                     */

#define U2DCSR(x)	(0x0100 + ((x) << 2))	/*                                          */
#define U2DCSR_BF	(1 << 10)	/*                          */
#define U2DCSR_BE	(1 << 10)	/*                          */
#define U2DCSR_DPE	(1 << 9)	/*                                     */
#define U2DCSR_FEF	(1 << 8)	/*                     */
#define U2DCSR_SP	(1 << 7)	/*                                                         */
#define U2DCSR_BNE	(1 << 6)	/*                               */
#define U2DCSR_BNF	(1 << 6)	/*                             */
#define U2DCSR_FST	(1 << 5)	/*                          */
#define U2DCSR_SST	(1 << 4)	/*                           */
#define U2DCSR_DME	(1 << 3)	/*            */
#define U2DCSR_TRN	(1 << 2)	/*                          */
#define U2DCSR_PC	(1 << 1)	/*                                */
#define U2DCSR_FS	(1 << 0)	/*                    */

#define U2DBCR0		(0x0200)		/*                                      */
#define U2DBCR(x)	(0x0200 + ((x) << 2))	/*                                      */

#define U2DDR0		(0x0300)		/*                                */

#define U2DEPCR(x)	(0x0400 + ((x) << 2))	/*                                         */
#define U2DEPCR_EE	(1 << 0)		/*                 */
#define U2DEPCR_BS_MASK	(0x3FE)			/*                                              */

#define U2DSCA		(0x0500)		/*                           */
#define U2DSCA_VALUE	(0x0120)

#define U2DEN0		(0x0504)		/*                                                */
#define U2DEN(x)	(0x0504 + ((x) << 2))	/*                                                */

/*                 */
#define U2DMACSR0		(0x1000)	/*                                           */
#define U2DMACSR(x)		(0x1000 + ((x) << 2))	/*                                           */
#define U2DMACSR_RUN		(1 << 31)	/*                        */
#define U2DMACSR_STOPIRQEN	(1 << 29)	/*                                      */
#define U2DMACSR_EORIRQEN	(1 << 28)	/*                                       */
#define U2DMACSR_EORJMPEN	(1 << 27)	/*                                */
#define U2DMACSR_EORSTOPEN	(1 << 26)	/*                */
#define U2DMACSR_RASIRQEN	(1 << 23)	/*                                                */
#define U2DMACSR_MASKRUN	(1 << 22)	/*          */
#define U2DMACSR_SCEMC		(3 << 18)	/*                                                 */
#define U2DMACSR_SCEMI		(0x1f << 13)	/*                                                 */
#define U2DMACSR_BUSERRTYPE	(7 << 10)	/*                   */
#define U2DMACSR_EORINTR	(1 << 9)	/*                */
#define U2DMACSR_REQPEND	(1 << 8)	/*                 */
#define U2DMACSR_RASINTR	(1 << 4)	/*                                                      */
#define U2DMACSR_STOPINTR	(1 << 3)	/*                            */
#define U2DMACSR_ENDINTR	(1 << 2)	/*                                      */
#define U2DMACSR_STARTINTR	(1 << 1)	/*                                        */
#define U2DMACSR_BUSERRINTR	(1 << 0)	/*                                            */

#define U2DMACR		(0x1080)		/*                        */
#define U2DMAINT	(0x10F0)		/*                          */

#define U2DMABR0	(0x1100)		/*                                   */
#define U2DMABR(x)      (0x1100 + (x) << 2)	/*                                   */

#define U2DMADADR0      (0x1200)		/*                                               */
#define U2DMADADR(x)    (0x1200 + (x) * 0x10)	/*                                               */

#define U2DMADADR_STOP	(1U << 0)

#define U2DMASADR0	(0x1204)		/*                                           */
#define U2DMASADR(x)	(0x1204 + (x) * 0x10)	/*                                           */
#define U2DMATADR0	(0x1208)		/*                                           */
#define U2DMATADR(x)	(0x1208 + (x) * 0x10)	/*                                           */

#define U2DMACMDR0	(0x120C)		/*                                            */
#define U2DMACMDR(x)	(0x120C + (x) * 0x10)	/*                                            */

#define U2DMACMDR_XFRDIS	(1 << 31)	/*                    */
#define U2DMACMDR_STARTIRQEN	(1 << 22)	/*                        */
#define U2DMACMDR_ENDIRQEN	(1 << 21)	/*                      */
#define U2DMACMDR_PACKCOMP	(1 << 13)	/*                 */
#define U2DMACMDR_LEN		(0x07ff)	/*                            */

#endif /*                         */
