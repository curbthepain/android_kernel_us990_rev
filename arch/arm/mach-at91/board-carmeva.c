/*
 * linux/arch/arm/mach-at91/board-carmeva.c
 *
 *  Copyright (c) 2005 Peer Georgi
 *  		       Conitec Datasystems
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

#include <linux/types.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/irq.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>

#include <mach/hardware.h>
#include <mach/board.h>

#include "generic.h"


static void __init carmeva_init_early(void)
{
	/*                                          */
	at91_initialize(20000000);

	/*                               */
	at91_register_uart(0, 0, 0);

	/*                                                        */
	at91_register_uart(AT91RM9200_ID_US1, 1, ATMEL_UART_CTS | ATMEL_UART_RTS
			   | ATMEL_UART_DTR | ATMEL_UART_DSR | ATMEL_UART_DCD
			   | ATMEL_UART_RI);

	/*                                        */
	at91_set_serial_console(0);
}

static struct macb_platform_data __initdata carmeva_eth_data = {
	.phy_irq_pin	= AT91_PIN_PC4,
	.is_rmii	= 1,
};

static struct at91_usbh_data __initdata carmeva_usbh_data = {
	.ports		= 2,
	.vbus_pin	= {-EINVAL, -EINVAL},
	.overcurrent_pin= {-EINVAL, -EINVAL},
};

static struct at91_udc_data __initdata carmeva_udc_data = {
	.vbus_pin	= AT91_PIN_PD12,
	.pullup_pin	= AT91_PIN_PD9,
};

/*                       */
//                                                          
//                         
//                         
	//                    
	//                    
//   

static struct at91_mmc_data __initdata carmeva_mmc_data = {
	.slot_b		= 0,
	.wire4		= 1,
	.det_pin	= AT91_PIN_PB10,
	.wp_pin		= AT91_PIN_PC14,
	.vcc_pin	= -EINVAL,
};

static struct spi_board_info carmeva_spi_devices[] = {
	{ /*                */
		.modalias = "mtd_dataflash",
		.chip_select  = 0,
		.max_speed_hz = 10 * 1000 * 1000,
	},
	{ /*                                    */
		.modalias = "spi-cs1",
		.chip_select  = 1,
		.max_speed_hz = 250 *  1000,
	},
	{ /*                                  */
		.modalias = "spi-cs2",
		.chip_select  = 2,
		.max_speed_hz = 1 * 1000 *  1000,
	},
	{ /*                                   */
		.modalias = "spi-cs3",
		.chip_select  = 3,
		.max_speed_hz = 10 * 1000 *  1000,
	},
};

static struct gpio_led carmeva_leds[] = {
	{ /*                    */
		.name			= "led9",
		.gpio			= AT91_PIN_PA21,
		.active_low		= 1,
		.default_trigger	= "heartbeat",
	},
	{ /*                     */
		.name			= "led10",
		.gpio			= AT91_PIN_PA25,
		.active_low		= 1,
	},
	{ /*                     */
		.name			= "led11",
		.gpio			= AT91_PIN_PA26,
		.active_low		= 1,
	},
	{ /*                     */
		.name			= "led12",
		.gpio			= AT91_PIN_PA18,
		.active_low		= 1,
	}
};

static void __init carmeva_board_init(void)
{
	/*        */
	at91_add_device_serial();
	/*          */
	at91_add_device_eth(&carmeva_eth_data);
	/*          */
	at91_add_device_usbh(&carmeva_usbh_data);
	/*            */
	at91_add_device_udc(&carmeva_udc_data);
	/*     */
	at91_add_device_i2c(NULL, 0);
	/*     */
	at91_add_device_spi(carmeva_spi_devices, ARRAY_SIZE(carmeva_spi_devices));
	/*               */
//                                      
	/*     */
	at91_add_device_mmc(0, &carmeva_mmc_data);
	/*      */
	at91_gpio_leds(carmeva_leds, ARRAY_SIZE(carmeva_leds));
}

MACHINE_START(CARMEVA, "Carmeva")
	/*                                 */
	.timer		= &at91rm9200_timer,
	.map_io		= at91_map_io,
	.init_early	= carmeva_init_early,
	.init_irq	= at91_init_irq_default,
	.init_machine	= carmeva_board_init,
MACHINE_END
