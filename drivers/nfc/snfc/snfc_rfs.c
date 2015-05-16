/*
              
  
 */


#include "snfc_rfs.h"

extern struct snfc_gp snfc_gpios;

/*
               
         
          
 */
static int snfc_rfs_open (struct inode *inode, struct file *fp)
{
    int rc = 0;

    SNFC_DEBUG_MSG_LOW("[snfc_rfs] snfc_rfs_open - start \n");

    SNFC_DEBUG_MSG_LOW("[snfc_rfs] snfc_rfs_open - end \n");

    return rc;
}


/*
               
         
                                   
 */
static ssize_t snfc_rfs_read(struct file *pf, char *pbuf, size_t size, loff_t *pos)
{
    int rc = 0;
    int getvalue = GPIO_LOW_VALUE;
    int rfonoff;

    SNFC_DEBUG_MSG_LOW("[snfc_rfs] snfc_rfs_read - start \n");

    /*                  */
    if(pf == NULL || pbuf == NULL /*               */ /*             */)
    {
        SNFC_DEBUG_MSG("[snfc_rfs] parameters ERROR pf = %p, pbuf = %p, size = %d, pos = %p\n",pf,pbuf,(int)size,pos);
        return -1;
    }

    /*                */
    getvalue = snfc_gpio_read(snfc_gpios.gpio_rfs);

    if((getvalue != GPIO_LOW_VALUE)&&(getvalue != GPIO_HIGH_VALUE))
    {
        SNFC_DEBUG_MSG("[snfc_rfs] ERROR - getvalue is out of range \n");
        return -2;
    }

    /*                           */
    //                                                      
    SNFC_DEBUG_MSG_LOW("[snfc_rfs] RFS pin status : %d \n", getvalue);

    if(getvalue)
        rfonoff = 0;
    else
        rfonoff = 1;

    SNFC_DEBUG_MSG_LOW("[snfc_rfs] rf status : %d \n", rfonoff);

    rc = copy_to_user((void*)pbuf, (void*)&rfonoff, size);
    if(rc)
    {
        SNFC_DEBUG_MSG("[snfc_rfs] ERROR -  copy_to_user \n");
        return rc;
    }

    SNFC_DEBUG_MSG_LOW("[snfc_rfs] snfc_rfs_read - end \n");

    return size;
}

/*
               
         
          
 */
static int snfc_rfs_release (struct inode *inode, struct file *fp)
{

    SNFC_DEBUG_MSG_LOW("[snfc_rfs] snfc_rfs_release - start \n");

    SNFC_DEBUG_MSG_LOW("[snfc_rfs] snfc_rfs_release - end \n");

    return 0;
}

static struct file_operations snfc_rfs_fops =
{
    .owner    = THIS_MODULE,
    .open      = snfc_rfs_open,
    .read      = snfc_rfs_read,
    .release  = snfc_rfs_release,
};

static struct miscdevice snfc_rfs_device = {
    .minor = 125,
    .name = "snfc_rfs",
    .fops = &snfc_rfs_fops,
};

int snfc_rfs_probe(struct device_node *np)
{
    int rc = 0;

        /*                          */
    rc = misc_register(&snfc_rfs_device);
    if (rc < 0)
    {
        SNFC_DEBUG_MSG("[snfc_rfs] FAIL!! can not register snfc_rfs \n");
        return rc;
    }

    snfc_gpios.gpio_rfs = of_get_named_gpio_flags(np, "sony,rfs-gpio", 0, NULL);
    rc = gpio_request(snfc_gpios.gpio_rfs, "snfc_rfs");
    if (rc)
    {
        SNFC_DEBUG_MSG("[snfc_rfs] gpio_request snfc_rfs fail\n");
    }

    return rc;
}
void snfc_rfs_remove(void)
{
    /*                            */
    misc_deregister(&snfc_rfs_device);
}
#if 0
static int snfc_rfs_init(void)
{
    int rc = 0;

    SNFC_DEBUG_MSG_LOW("[snfc_rfs] snfc_rfs_init - start \n");

    SNFC_DEBUG_MSG_LOW("[snfc_rfs] snfc_rfs_init - end \n");

    return rc;
}

static void snfc_rfs_exit(void)
{
    SNFC_DEBUG_MSG_LOW("[snfc_rfs] snfc_rfs_exit - start \n");

    SNFC_DEBUG_MSG_LOW("[snfc_rfs] snfc_rfs_exit - end \n");
}

module_init(snfc_rfs_init);
module_exit(snfc_rfs_exit);
#endif
MODULE_LICENSE("Dual BSD/GPL");

