/* linux/arch/arm/mach-s5pc100/include/mach/map.h
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Copyright 2009 Samsung Electronics Co.
 *	Byungho Min <bhmin@samsung.com>
 *
 * S5PC100 - Memory map definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_MAP_H
#define __ASM_ARCH_MAP_H __FILE__

#include <plat/map-base.h>
#include <plat/map-s5p.h>

#define S5PC100_PA_SDRAM		0x20000000

#define S5PC100_PA_ONENAND		0xE7100000
#define S5PC100_PA_ONENAND_BUF		0xB0000000

#define S5PC100_PA_CHIPID		0xE0000000

#define S5PC100_PA_SYSCON		0xE0100000

#define S5PC100_PA_OTHERS		0xE0200000

#define S5PC100_PA_GPIO			0xE0300000

#define S5PC100_PA_VIC0			0xE4000000
#define S5PC100_PA_VIC1			0xE4100000
#define S5PC100_PA_VIC2			0xE4200000

#define S5PC100_PA_SROMC		0xE7000000

#define S5PC100_PA_CFCON		0xE7800000

#define S5PC100_PA_MDMA			0xE8100000
#define S5PC100_PA_PDMA0		0xE9000000
#define S5PC100_PA_PDMA1		0xE9200000

#define S5PC100_PA_TIMER		0xEA000000
#define S5PC100_PA_SYSTIMER		0xEA100000
#define S5PC100_PA_WATCHDOG		0xEA200000
#define S5PC100_PA_RTC			0xEA300000

#define S5PC100_PA_UART			0xEC000000

#define S5PC100_PA_IIC0			0xEC100000
#define S5PC100_PA_IIC1			0xEC200000

#define S5PC100_PA_SPI0			0xEC300000
#define S5PC100_PA_SPI1			0xEC400000
#define S5PC100_PA_SPI2			0xEC500000

#define S5PC100_PA_USB_HSOTG		0xED200000
#define S5PC100_PA_USB_HSPHY		0xED300000

#define S5PC100_PA_HSMMC(x)		(0xED800000 + ((x) * 0x100000))

#define S5PC100_PA_FB			0xEE000000

#define S5PC100_PA_FIMC0		0xEE200000
#define S5PC100_PA_FIMC1		0xEE300000
#define S5PC100_PA_FIMC2		0xEE400000

#define S5PC100_PA_I2S0			0xF2000000
#define S5PC100_PA_I2S1			0xF2100000
#define S5PC100_PA_I2S2			0xF2200000

#define S5PC100_PA_AC97			0xF2300000

#define S5PC100_PA_PCM0			0xF2400000
#define S5PC100_PA_PCM1			0xF2500000

#define S5PC100_PA_SPDIF		0xF2600000

#define S5PC100_PA_TSADC		0xF3000000

#define S5PC100_PA_KEYPAD		0xF3100000

/*                       */

#define S3C_PA_FB			S5PC100_PA_FB
#define S3C_PA_HSMMC0			S5PC100_PA_HSMMC(0)
#define S3C_PA_HSMMC1			S5PC100_PA_HSMMC(1)
#define S3C_PA_HSMMC2			S5PC100_PA_HSMMC(2)
#define S3C_PA_IIC			S5PC100_PA_IIC0
#define S3C_PA_IIC1			S5PC100_PA_IIC1
#define S3C_PA_KEYPAD			S5PC100_PA_KEYPAD
#define S3C_PA_ONENAND			S5PC100_PA_ONENAND
#define S3C_PA_ONENAND_BUF		S5PC100_PA_ONENAND_BUF
#define S3C_PA_RTC			S5PC100_PA_RTC
#define S3C_PA_TSADC			S5PC100_PA_TSADC
#define S3C_PA_USB_HSOTG		S5PC100_PA_USB_HSOTG
#define S3C_PA_USB_HSPHY		S5PC100_PA_USB_HSPHY
#define S3C_PA_WDT			S5PC100_PA_WATCHDOG
#define S3C_PA_SPI0			S5PC100_PA_SPI0
#define S3C_PA_SPI1			S5PC100_PA_SPI1
#define S3C_PA_SPI2			S5PC100_PA_SPI2

#define S5P_PA_CHIPID			S5PC100_PA_CHIPID
#define S5P_PA_FIMC0			S5PC100_PA_FIMC0
#define S5P_PA_FIMC1			S5PC100_PA_FIMC1
#define S5P_PA_FIMC2			S5PC100_PA_FIMC2
#define S5P_PA_SDRAM			S5PC100_PA_SDRAM
#define S5P_PA_SROMC			S5PC100_PA_SROMC
#define S5P_PA_SYSCON			S5PC100_PA_SYSCON
#define S5P_PA_TIMER			S5PC100_PA_TIMER

#define SAMSUNG_PA_ADC			S5PC100_PA_TSADC
#define SAMSUNG_PA_CFCON		S5PC100_PA_CFCON
#define SAMSUNG_PA_KEYPAD		S5PC100_PA_KEYPAD

#define S5PC100_VA_OTHERS		(S3C_VA_SYS + 0x10000)

#define S3C_SZ_ONENAND_BUF		(SZ_256M - SZ_32M)

/*      */

#define S3C_PA_UART			S5PC100_PA_UART

#define S5P_PA_UART(x)			(S3C_PA_UART + ((x) * S3C_UART_OFFSET))
#define S5P_PA_UART0			S5P_PA_UART(0)
#define S5P_PA_UART1			S5P_PA_UART(1)
#define S5P_PA_UART2			S5P_PA_UART(2)
#define S5P_PA_UART3			S5P_PA_UART(3)

#define S5P_SZ_UART			SZ_256

#endif /*                  */