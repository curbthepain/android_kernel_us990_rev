/*
                
  
 */

/*
                              
 */
#include "felica_pon.h"
#include "felica_gpio.h"

#include "felica_test.h"

//                        
//                        
//      
/*
          
 */

//                                                                            
//                         

/*
                         
 */

static int isopen = 0; //                     

/*
                         
 */

/*
                                                                                                 
                                                             
              
                                   
*/
static int felica_pon_open (struct inode *inode, struct file *fp)
{
  int rc = 0;

  if(1 == isopen)
  {
    FELICA_DEBUG_MSG_HIGH("[FELICA_PON] felica_pon_open - already open \n");
    return -1;
  }
  else
  {
    FELICA_DEBUG_MSG_LOW("[FELICA_PON] felica_pon_open - start \n");
    isopen = 1;
  }

  rc = felica_gpio_open(GPIO_FELICA_PON, GPIO_DIRECTION_OUT, GPIO_LOW_VALUE);

#ifdef FELICA_UART_DEBUG
  mdelay(100);
  felica_uart_open();
#endif

  FELICA_DEBUG_MSG_LOW("[FELICA_PON] felica_pon_open - end \n");

#ifdef FELICA_FN_DEVICE_TEST
  FELICA_DEBUG_MSG_LOW("[FELICA_PON] felica_pon_open - result_open(%d)  \n",result_open_pon);
  return result_open_pon;
#else
  return rc;
#endif
}

/*
                                                                                                             
                                  
                                   
*/
static ssize_t felica_pon_write(struct file *fp, const char *buf, size_t count, loff_t *pos)
{
  int rc = 0;
  int SetValue = 0;

  FELICA_DEBUG_MSG_LOW("[FELICA_PON] felica_pon_write - start \n");

  //                                                                                        

  /*             */
	if(NULL == fp)
	{
	  FELICA_DEBUG_MSG_HIGH("[FELICA_PON] ERROR fp is NULL \n");

	  return -1;
	}
  
	if(NULL == buf)
	{
	  FELICA_DEBUG_MSG_HIGH("[FELICA_PON] ERROR buf is NULL \n");

	  return -1;
	}
  
	if(1 != count)
	{
	  FELICA_DEBUG_MSG_HIGH("[FELICA_PON] ERROR count(%d) \n",count);

	  return -1;
	}
  
	if(NULL == pos)
	{
	  FELICA_DEBUG_MSG_HIGH("[FELICA_PON] ERROR pos is NULL \n");

	  return -1;
	}

  rc = copy_from_user(&SetValue, (void*)buf, count);
  if(rc)
  {
    FELICA_DEBUG_MSG_HIGH("[FELICA_PON] ERROR - copy_from_user \n");

    return rc;
  }

  if((GPIO_LOW_VALUE != SetValue)&&(GPIO_HIGH_VALUE != SetValue))
  {
    FELICA_DEBUG_MSG_HIGH("[FELICA_PON] ERROR - SetValue is out of range \n");

    return -1;
  }
  else if(GPIO_LOW_VALUE != SetValue)
  {
    FELICA_DEBUG_MSG_HIGH("[FELICA_PON] ========> ON \n");

  }
  else if(GPIO_HIGH_VALUE != SetValue)
  {
    FELICA_DEBUG_MSG_HIGH("[FELICA_PON] <======== OFF \n");
  }

  felica_gpio_write(GPIO_FELICA_PON, SetValue);

  mdelay(20);

#ifdef FELICA_UART_DEBUG
  if (SetValue == 1)
  {
    int len, i;
    char buf[256];

    len = felica_uart_read(buf, 256);

    for (i = 0; i < len; i++)
     pr_info("%s: felica_uart_read [%d] 0x%02X\n", __func__, i, buf[i]);
  }
#endif

#ifdef FELICA_FN_DEVICE_TEST
    FELICA_DEBUG_MSG_LOW("[FELICA_PON] felica_pon_write - result_write_pon(%d) \n",result_write_pon);
    return result_write_pon;
#else
    return 1;
#endif
}

/*
                                                                                                  
                                                             
              
                                   
*/
static int felica_pon_release (struct inode *inode, struct file *fp)
{
  if(0 == isopen)
  {
    FELICA_DEBUG_MSG_HIGH("[FELICA_PON] felica_pon_release - not open \n");

    return -1;
  }
  else
  {
    FELICA_DEBUG_MSG_LOW("[FELICA_PON] felica_pon_release - start \n");

    isopen = 0;
  }

#ifdef FELICA_UART_DEBUG
  felica_uart_close();
#endif

  felica_gpio_write(GPIO_FELICA_PON, GPIO_LOW_VALUE);

  FELICA_DEBUG_MSG_LOW("[FELICA_PON] felica_pon_release - end \n");

#ifdef FELICA_FN_DEVICE_TEST
  FELICA_DEBUG_MSG_LOW("[FELICA_PON] felica_pon_close - result_close_pon(%d)  \n",result_close_pon);
  return result_close_pon;
#else
  return 0;
#endif

}

/*
                       
 */

static struct file_operations felica_pon_fops =
{
  .owner    = THIS_MODULE,
  .open      = felica_pon_open,
  .write    = felica_pon_write,
  .release  = felica_pon_release,
};

static struct miscdevice felica_pon_device =
{
  .minor = MINOR_NUM_FELICA_PON,
  .name = FELICA_PON_NAME,
  .fops = &felica_pon_fops,
};

static int felica_pon_init(void)
{
  int rc = 0;

  FELICA_DEBUG_MSG_LOW("[FELICA_PON] felica_pon_init - start \n");

  /*                          */
  rc = misc_register(&felica_pon_device);
  if (rc)
  {
    FELICA_DEBUG_MSG_HIGH("[FELICA_PON] ERROR can not register felica_pon \n");

    return rc;
  }

  FELICA_DEBUG_MSG_LOW("[FELICA_PON] felica_pon_init - end \n");

  return 0;
}

static void felica_pon_exit(void)
{
  FELICA_DEBUG_MSG_LOW("[FELICA_PON] felica_pon_exit - start \n");

  /*                            */
  misc_deregister(&felica_pon_device);

  FELICA_DEBUG_MSG_LOW("[FELICA_PON] felica_pon_exit - end \n");
}

module_init(felica_pon_init);
module_exit(felica_pon_exit);

MODULE_LICENSE("Dual BSD/GPL");
