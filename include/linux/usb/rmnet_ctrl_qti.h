#ifndef __LINUX_USB_U_RMNET_CTRL_QTI_H
#define __LINUX_USB_U_RMNET_CTRL_QTI_H

#include <linux/ioctl.h>

#define MAX_QTI_PKT_SIZE 2048

#define FRMNET_CTRL_IOCTL_MAGIC	'r'
#define FRMNET_CTRL_GET_LINE_STATE	_IOR(FRMNET_CTRL_IOCTL_MAGIC, 2, int)


#endif /*                                */
