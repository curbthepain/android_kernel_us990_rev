/*
 * arch/arm/mach-pxa/include/mach/pcm990_baseboard.h
 *
 * (c) 2003 Phytec Messtechnik GmbH <armlinux@phytec.de>
 * (c) 2007 Juergen Beisert <j.beisert@pengutronix.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <mach/pcm027.h>

/*
                                             
                                   
 */

/*                                                            */
#define PCM990_CTRL_INT_IRQ_GPIO	9
#define PCM990_CTRL_INT_IRQ		PXA_GPIO_TO_IRQ(PCM990_CTRL_INT_IRQ_GPIO)
#define PCM990_CTRL_INT_IRQ_EDGE	IRQ_TYPE_EDGE_RISING
#define PCM990_CTRL_PHYS		PXA_CS1_PHYS	/*        */
#define PCM990_CTRL_BASE		0xea000000
#define PCM990_CTRL_SIZE		(1*1024*1024)

#define PCM990_CTRL_PWR_IRQ_GPIO	14
#define PCM990_CTRL_PWR_IRQ		PXA_GPIO_TO_IRQ(PCM990_CTRL_PWR_IRQ_GPIO)
#define PCM990_CTRL_PWR_IRQ_EDGE	IRQ_TYPE_EDGE_RISING

/*                             */
#define PCM990_CTRL_REG0	0x0000	/*                */
#define PCM990_CTRL_SYSRES	0x0001	/*                       */
#define PCM990_CTRL_RESOUT	0x0002	/*                          */
#define PCM990_CTRL_RESGPIO	0x0004	/*                           */

#define PCM990_CTRL_REG1	0x0002	/*                */
#define PCM990_CTRL_5VOFF	0x0001	/*                        */
#define PCM990_CTRL_CANPWR	0x0004	/*                    */
#define PCM990_CTRL_PM_5V	0x0008	/*            */

#define PCM990_CTRL_REG2	0x0004	/*              */
#define PCM990_CTRL_LEDPWR	0x0001	/*                  */
#define PCM990_CTRL_LEDBAS	0x0002	/*                  */
#define PCM990_CTRL_LEDUSR	0x0004	/*                 */

#define PCM990_CTRL_REG3	0x0006	/*                     */
#define PCM990_CTRL_LCDPWR	0x0001	/*                 */
#define PCM990_CTRL_LCDON	0x0002	/*                 */
#define PCM990_CTRL_LCDPOS1	0x0004	/*          */
#define PCM990_CTRL_LCDPOS2	0x0008	/*          */

#define PCM990_CTRL_REG4	0x0008	/*                      */
#define PCM990_CTRL_MMC1PWR	0x0001 /*                  */

#define PCM990_CTRL_REG5	0x000A	/*                      */
#define PCM990_CTRL_MMC2PWR	0x0001	/*                  */
#define PCM990_CTRL_MMC2LED	0x0002	/*             */
#define PCM990_CTRL_MMC2DE	0x0004	/*                    */
#define PCM990_CTRL_MMC2WP	0x0008	/*                           */

#define PCM990_CTRL_REG6	0x000C	/*                          */
#define PCM990_CTRL_INTC0	0x0001	/*                     */
#define PCM990_CTRL_INTC1	0x0002	/*                 */
#define PCM990_CTRL_INTC2	0x0004	/*                       */
#define PCM990_CTRL_INTC3	0x0008	/*                     */

#define PCM990_CTRL_REG7	0x000E	/*                           */
#define PCM990_CTRL_ENAINT0	0x0001	/*                      */
#define PCM990_CTRL_ENAINT1	0x0002	/*                  */
#define PCM990_CTRL_ENAINT2	0x0004	/*                        */
#define PCM990_CTRL_ENAINT3	0x0008	/*                      */

#define PCM990_CTRL_REG8	0x0014	/*               */
#define PCM990_CTRL_FFSD	0x0001	/*                */
#define PCM990_CTRL_BTSD	0x0002	/*                */
#define PCM990_CTRL_FFRI	0x0004	/*                   */
#define PCM990_CTRL_BTRX	0x0008	/*                   */

#define PCM990_CTRL_REG9	0x0010	/*                     */
#define PCM990_CTRL_FLWP	0x0001	/*                        */
#define PCM990_CTRL_FLDIS	0x0002	/*                  */
#define PCM990_CTRL_AC97ENA	0x0004	/*                       */

#define PCM990_CTRL_REG10	0x0012	/*              */
#define PCM990_CTRL_GPSPWR	0x0004	/*                    */
#define PCM990_CTRL_GPSENA	0x0008	/*                  */

#define PCM990_CTRL_REG11	0x0014	/*               */
#define PCM990_CTRL_ACENA	0x0001	/*               */
#define PCM990_CTRL_ACSEL	0x0002	/*                          */
#define PCM990_CTRL_ACPRES	0x0004	/*            */
#define PCM990_CTRL_ACALARM	0x0008	/*            */

#define PCM990_CTRL_P2V(x)	((x) - PCM990_CTRL_PHYS + PCM990_CTRL_BASE)
#define PCM990_CTRL_V2P(x)	((x) - PCM990_CTRL_BASE + PCM990_CTRL_PHYS)

#ifndef __ASSEMBLY__
#  define __PCM990_CTRL_REG(x) \
		(*((volatile unsigned char *)PCM990_CTRL_P2V(x)))
#else
#  define __PCM990_CTRL_REG(x)	PCM990_CTRL_P2V(x)
#endif

#define PCM990_INTMSKENA __PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG7)
#define PCM990_INTSETCLR __PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG6)
#define PCM990_CTRL0	__PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG0)
#define PCM990_CTRL1	__PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG1)
#define PCM990_CTRL2	__PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG2)
#define PCM990_CTRL3	__PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG3)
#define PCM990_CTRL4	__PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG4)
#define PCM990_CTRL5	__PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG5)
#define PCM990_CTRL6	__PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG6)
#define PCM990_CTRL7	__PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG7)
#define PCM990_CTRL8	__PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG8)
#define PCM990_CTRL9	__PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG9)
#define PCM990_CTRL10	__PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG10)
#define PCM990_CTRL11	__PCM990_CTRL_REG(PCM990_CTRL_PHYS + PCM990_CTRL_REG11)


/*
      
 */
#define PCM990_IDE_IRQ_GPIO	13
#define PCM990_IDE_IRQ		PXA_GPIO_TO_IRQ(PCM990_IDE_IRQ_GPIO)
#define PCM990_IDE_IRQ_EDGE	IRQ_TYPE_EDGE_RISING
#define PCM990_IDE_PLD_PHYS	0x20000000	/*             */
#define PCM990_IDE_PLD_BASE	0xee000000
#define PCM990_IDE_PLD_SIZE	(1*1024*1024)

/*                             */
#define PCM990_IDE_PLD_REG0	0x1000	/*                       */
#define PCM990_IDE_PM5V		0x0004	/*                 */
#define PCM990_IDE_STBY		0x0008	/*                  */

#define PCM990_IDE_PLD_REG1	0x1002	/*                       */
#define PCM990_IDE_IDEMODE	0x0001	/*                */
#define PCM990_IDE_DMAENA	0x0004	/*               */
#define PCM990_IDE_DMA1_0	0x0008	/*                    */

#define PCM990_IDE_PLD_REG2	0x1004	/*                       */
#define PCM990_IDE_RESENA	0x0001	/*                         */
#define PCM990_IDE_RES		0x0002	/*                  */
#define PCM990_IDE_RDY		0x0008	/*     */

#define PCM990_IDE_PLD_REG3	0x1006	/*                       */
#define PCM990_IDE_IDEOE	0x0001	/*                     */
#define PCM990_IDE_IDEON	0x0002	/*                             */
#define PCM990_IDE_IDEIN	0x0004	/*                            */

#define PCM990_IDE_PLD_REG4	0x1008	/*                       */
#define PCM990_IDE_PWRENA	0x0001	/*                     */
#define PCM990_IDE_5V		0x0002	/*                */
#define PCM990_IDE_PWG		0x0008	/*                   */

#define PCM990_IDE_PLD_P2V(x) ((x) - PCM990_IDE_PLD_PHYS + PCM990_IDE_PLD_BASE)
#define PCM990_IDE_PLD_V2P(x) ((x) - PCM990_IDE_PLD_BASE + PCM990_IDE_PLD_PHYS)

#ifndef __ASSEMBLY__
# define  __PCM990_IDE_PLD_REG(x) \
	(*((volatile unsigned char *)PCM990_IDE_PLD_P2V(x)))
#else
# define  __PCM990_IDE_PLD_REG(x)	PCM990_IDE_PLD_P2V(x)
#endif

#define PCM990_IDE0 \
	__PCM990_IDE_PLD_REG(PCM990_IDE_PLD_PHYS + PCM990_IDE_PLD_REG0)
#define PCM990_IDE1 \
	__PCM990_IDE_PLD_REG(PCM990_IDE_PLD_PHYS + PCM990_IDE_PLD_REG1)
#define PCM990_IDE2 \
	__PCM990_IDE_PLD_REG(PCM990_IDE_PLD_PHYS + PCM990_IDE_PLD_REG2)
#define PCM990_IDE3 \
	__PCM990_IDE_PLD_REG(PCM990_IDE_PLD_PHYS + PCM990_IDE_PLD_REG3)
#define PCM990_IDE4 \
	__PCM990_IDE_PLD_REG(PCM990_IDE_PLD_PHYS + PCM990_IDE_PLD_REG4)

/*
                
 */
#define PCM990_CF_IRQ_GPIO	11
#define PCM990_CF_IRQ		PXA_GPIO_TO_IRQ(PCM990_CF_IRQ_GPIO)
#define PCM990_CF_IRQ_EDGE	IRQ_TYPE_EDGE_RISING

#define PCM990_CF_CD_GPIO	12
#define PCM990_CF_CD		PXA_GPIO_TO_IRQ(PCM990_CF_CD_GPIO)
#define PCM990_CF_CD_EDGE	IRQ_TYPE_EDGE_RISING

#define PCM990_CF_PLD_PHYS	0x30000000	/*             */
#define PCM990_CF_PLD_BASE	0xef000000
#define PCM990_CF_PLD_SIZE	(1*1024*1024)
#define PCM990_CF_PLD_P2V(x)	((x) - PCM990_CF_PLD_PHYS + PCM990_CF_PLD_BASE)
#define PCM990_CF_PLD_V2P(x)	((x) - PCM990_CF_PLD_BASE + PCM990_CF_PLD_PHYS)

/*                             */
#define PCM990_CF_PLD_REG0	0x1000	/*                      */
#define PCM990_CF_REG0_LED	0x0001	/*           */
#define PCM990_CF_REG0_BLK	0x0002	/*                          */
#define PCM990_CF_REG0_PM5V	0x0004	/*                        */
#define PCM990_CF_REG0_STBY	0x0008	/*                  */

#define PCM990_CF_PLD_REG1	0x1002	/*                      */
#define PCM990_CF_REG1_IDEMODE	0x0001	/*                           */
#define PCM990_CF_REG1_CF0	0x0002	/*                               */

#define PCM990_CF_PLD_REG2	0x1004	/*                      */
#define PCM990_CF_REG2_RES	0x0002	/*                 */
#define PCM990_CF_REG2_RDYENA	0x0004	/*                  */
#define PCM990_CF_REG2_RDY	0x0008	/*                    */

#define PCM990_CF_PLD_REG3	0x1006	/*                      */
#define PCM990_CF_REG3_CFOE	0x0001	/*                     */
#define PCM990_CF_REG3_CFON	0x0002	/*                             */
#define PCM990_CF_REG3_CFIN	0x0004	/*                            */
#define PCM990_CF_REG3_CFCD	0x0008	/*                             */

#define PCM990_CF_PLD_REG4	0x1008	/*                      */
#define PCM990_CF_REG4_PWRENA	0x0001	/*                               */
#define PCM990_CF_REG4_5_3V	0x0002	/*                                 */
#define PCM990_CF_REG4_3B	0x0004	/*                                  */
#define PCM990_CF_REG4_PWG	0x0008	/*                  */

#define PCM990_CF_PLD_REG5	0x100A	/*                      */
#define PCM990_CF_REG5_BVD1	0x0001	/*            */
#define PCM990_CF_REG5_BVD2	0x0002	/*            */
#define PCM990_CF_REG5_VS1	0x0004	/*           */
#define PCM990_CF_REG5_VS2	0x0008	/*           */

#define PCM990_CF_PLD_REG6	0x100C	/*                      */
#define PCM990_CF_REG6_CD1	0x0001	/*                   */
#define PCM990_CF_REG6_CD2	0x0002	/*                   */

#ifndef __ASSEMBLY__
#  define  __PCM990_CF_PLD_REG(x) \
	(*((volatile unsigned char *)PCM990_CF_PLD_P2V(x)))
#else
#  define  __PCM990_CF_PLD_REG(x)	PCM990_CF_PLD_P2V(x)
#endif

#define PCM990_CF0 __PCM990_CF_PLD_REG(PCM990_CF_PLD_PHYS + PCM990_CF_PLD_REG0)
#define PCM990_CF1 __PCM990_CF_PLD_REG(PCM990_CF_PLD_PHYS + PCM990_CF_PLD_REG1)
#define PCM990_CF2 __PCM990_CF_PLD_REG(PCM990_CF_PLD_PHYS + PCM990_CF_PLD_REG2)
#define PCM990_CF3 __PCM990_CF_PLD_REG(PCM990_CF_PLD_PHYS + PCM990_CF_PLD_REG3)
#define PCM990_CF4 __PCM990_CF_PLD_REG(PCM990_CF_PLD_PHYS + PCM990_CF_PLD_REG4)
#define PCM990_CF5 __PCM990_CF_PLD_REG(PCM990_CF_PLD_PHYS + PCM990_CF_PLD_REG5)
#define PCM990_CF6 __PCM990_CF_PLD_REG(PCM990_CF_PLD_PHYS + PCM990_CF_PLD_REG6)

/*
                     
 */
#define PCM990_AC97_IRQ_GPIO	10
#define PCM990_AC97_IRQ		PXA_GPIO_TO_IRQ(PCM990_AC97_IRQ_GPIO)
#define PCM990_AC97_IRQ_EDGE	IRQ_TYPE_EDGE_RISING

/*
              
 */
#define PCM990_MMC0_IRQ_GPIO	9
#define PCM990_MMC0_IRQ		PXA_GPIO_TO_IRQ(PCM990_MMC0_IRQ_GPIO)
#define PCM990_MMC0_IRQ_EDGE	IRQ_TYPE_EDGE_FALLING

/*
              
 */
#define PCM990_USB_OVERCURRENT (88 | GPIO_ALT_FN_1_IN)
#define PCM990_USB_PWR_EN (89 | GPIO_ALT_FN_2_OUT)
