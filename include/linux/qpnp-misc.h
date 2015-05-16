/* Copyright (c) 2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __QPNP_MISC_H
#define __QPNP_MISC_H

#include <linux/errno.h>

#ifdef CONFIG_QPNP_MISC
/* 
                                                         
  
                               
  
                                                                  
                                                              
  
                                                                         
                                                     
 */

int qpnp_misc_irqs_available(struct device *consumer_dev);
#else
static int qpnp_misc_irqs_available(struct device *consumer_dev)
{
	return 0;
}
#endif
#ifdef CONFIG_SMB349_CHARGER
/*                                               */
int smb349_pmic_usb_override(bool mode);
bool smb349_pmic_batt_present(void);
void smb349_pmic_reg_dump(void);
#endif
#endif
