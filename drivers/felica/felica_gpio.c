/*
                
  
 */

/*
                              
 */
#include <linux/gpio.h>

#include "felica_gpio.h"



/*                       */

/*
               
         
          
*/
int felica_gpio_open(int gpionum, int direction, int value)
{
  int rc = 0;
  char int_name[30];

  if(direction == GPIO_DIRECTION_IN)
  {
    rc = gpio_tlmm_config(GPIO_CFG(gpionum, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA), GPIO_CONFIG_ENABLE);

  if(rc)
  {
    FELICA_DEBUG_MSG_HIGH("[FELICA_GPIO] ERROR - gpio_tlmm_config \n");

    return rc;
  }

    if(GPIO_FELICA_INT == gpionum)
  {
      sprintf(int_name, "felica_int_%02d", gpionum);

      gpio_request(gpionum, int_name);
    }
#ifdef FELICA_LED_SUPPORT
	if(GPIO_FELICA_RFS == gpionum)
	{
		sprintf(int_name, "felica_rfs_%02d", gpionum);
		gpio_request(gpionum, int_name);
	}
#endif
    rc = gpio_direction_input((unsigned)gpionum);

    if(rc)
    {
      FELICA_DEBUG_MSG_HIGH("[FELICA_GPIO] ERROR -  gpio_direction_input \n");

      return rc;
    }
  }
  else
  {
    rc = gpio_tlmm_config(GPIO_CFG(gpionum, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA), GPIO_CONFIG_ENABLE);

    if(rc)
    {
      FELICA_DEBUG_MSG_HIGH("[FELICA_GPIO] ERROR - gpio_tlmm_config \n");

      return rc;
    }
	if(GPIO_FELICA_PON == gpionum)
	{
		sprintf(int_name, "felica_pon_%02d", gpionum);
		gpio_request(gpionum, int_name);
	}

    rc = gpio_direction_output((unsigned)gpionum, value);

    if(rc)
    {
      FELICA_DEBUG_MSG_HIGH("[FELICA_GPIO] ERROR -  gpio_direction_output \n");

      return rc;
    }
  }

  return rc;
}

/*
               
         
          
*/
void felica_gpio_write(int gpionum, int value)
{
  gpio_set_value(gpionum, value);
}

/*
               
         
          
*/
int felica_gpio_read(int gpionum)
{
  return gpio_get_value(gpionum);
}
/*
               
         
          
*/
int felica_get_rfs_gpio_num(void)
{
/*                                                                         */

  int gpionum = GPIO_FELICA_RFS;


  FELICA_DEBUG_MSG_LOW("[FELICA_GPIO] felica_get_rfs_gpio_num(%d) \n",gpionum);

  return gpionum;
}

/*
               
         
          
*/
int felica_get_int_gpio_num(void)
{
/*                                                                         */	
#ifdef CONFIG_LGE_FELICA_NFC_DCM
  int gpionum = GPIO_FELICA_INT;

  if (lge_get_board_revno() < HW_REV_D)
  {
    gpionum = GPIO_FELICA_INT;
  }
  else
  {
    gpionum = GPIO_FELICA_INT_REV_D;  
  }
	FELICA_DEBUG_MSG_LOW("[FELICA_GPIO] felica_get_rws_gpio_num(%d) \n",gpionum);

	return gpionum;
#else	
	return GPIO_FELICA_INT;
#endif
}
