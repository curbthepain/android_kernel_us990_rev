/* Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
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

#include <linux/module.h>
#include <linux/types.h>
#include <linux/net.h>
#include <linux/socket.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/poll.h>
#include <linux/fcntl.h>
#include <linux/gfp.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/msm_ipc.h>
#include <linux/rwsem.h>

#include <asm/uaccess.h>

#include <net/sock.h>
#include "ipc_router.h"
#include "msm_ipc_router_security.h"

#define IRSC_COMPLETION_TIMEOUT_MS 30000
#define SEC_RULES_HASH_SZ 32

#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)-1)
#endif

struct security_rule {
	struct list_head list;
	uint32_t service_id;
	uint32_t instance_id;
	unsigned reserved;
	int num_group_info;
	gid_t *group_id;
};

static DECLARE_RWSEM(security_rules_lock_lha4);
static struct list_head security_rules[SEC_RULES_HASH_SZ];
static DECLARE_COMPLETION(irsc_completion);

/* 
                                                                          
                                                  
 */
void wait_for_irsc_completion(void)
{
	unsigned long rem_jiffies;
	do {
		rem_jiffies = wait_for_completion_timeout(&irsc_completion,
				msecs_to_jiffies(IRSC_COMPLETION_TIMEOUT_MS));
		if (rem_jiffies)
			return;
		pr_err("%s: waiting for IPC Security Conf.\n", __func__);
	} while (1);
}

/* 
                                                           
 */
void signal_irsc_completion(void)
{
	complete_all(&irsc_completion);
}

/* 
                                                                    
                                                                  
  
                                                            
 */
int check_permissions(void)
{
	int rc = 0;
	if (!current_euid() || in_egroup_p(AID_NET_RAW))
		rc = 1;
	return rc;
}
EXPORT_SYMBOL(check_permissions);

/* 
                                                                   
                                                   
  
                                                   
  
                                                                          
                                                                      
                                                                
 */
int msm_ipc_config_sec_rules(void *arg)
{
	struct config_sec_rules_args sec_rules_arg;
	struct security_rule *rule, *temp_rule;
	int key;
	size_t group_info_sz;
	int ret;

	if (current_euid())
		return -EPERM;

	ret = copy_from_user(&sec_rules_arg, (void *)arg,
			     sizeof(sec_rules_arg));
	if (ret)
		return -EFAULT;

	if (sec_rules_arg.num_group_info <= 0)
		return -EINVAL;

	if (sec_rules_arg.num_group_info > (SIZE_MAX / sizeof(gid_t))) {
		pr_err("%s: Integer Overflow %d * %d\n", __func__,
			sizeof(gid_t), sec_rules_arg.num_group_info);
		return -EINVAL;
	}
	group_info_sz = sec_rules_arg.num_group_info * sizeof(gid_t);

	rule = kzalloc(sizeof(struct security_rule), GFP_KERNEL);
	if (!rule) {
		pr_err("%s: security_rule alloc failed\n", __func__);
		return -ENOMEM;
	}

	rule->group_id = kzalloc(group_info_sz, GFP_KERNEL);
	if (!rule->group_id) {
		pr_err("%s: group_id alloc failed\n", __func__);
		kfree(rule);
		return -ENOMEM;
	}

	rule->service_id = sec_rules_arg.service_id;
	rule->instance_id = sec_rules_arg.instance_id;
	rule->reserved = sec_rules_arg.reserved;
	rule->num_group_info = sec_rules_arg.num_group_info;
	ret = copy_from_user(rule->group_id,
			     ((void *)(arg + sizeof(sec_rules_arg))),
			     group_info_sz);
	if (ret) {
		kfree(rule->group_id);
		kfree(rule);
		return -EFAULT;
	}

	key = rule->service_id & (SEC_RULES_HASH_SZ - 1);
	down_write(&security_rules_lock_lha4);
	if (rule->service_id == ALL_SERVICE) {
		temp_rule = list_first_entry(&security_rules[key],
					     struct security_rule, list);
		list_del(&temp_rule->list);
		kfree(temp_rule->group_id);
		kfree(temp_rule);
	}
	list_add_tail(&rule->list, &security_rules[key]);
	up_write(&security_rules_lock_lha4);

	if (rule->service_id == ALL_SERVICE)
		msm_ipc_sync_default_sec_rule((void *)rule);
	else
		msm_ipc_sync_sec_rule(rule->service_id, rule->instance_id,
				      (void *)rule);

	return 0;
}
EXPORT_SYMBOL(msm_ipc_config_sec_rules);

/* 
                                                         
  
                                       
  
                                                                     
                                                                    
                                                
 */
static int msm_ipc_add_default_rule(void)
{
	struct security_rule *rule;
	int key;

	rule = kzalloc(sizeof(struct security_rule), GFP_KERNEL);
	if (!rule) {
		pr_err("%s: security_rule alloc failed\n", __func__);
		return -ENOMEM;
	}

	rule->group_id = kzalloc(sizeof(int), GFP_KERNEL);
	if (!rule->group_id) {
		pr_err("%s: group_id alloc failed\n", __func__);
		kfree(rule);
		return -ENOMEM;
	}

	rule->service_id = ALL_SERVICE;
	rule->instance_id = ALL_INSTANCE;
	rule->num_group_info = 1;
	*(rule->group_id) = AID_NET_RAW;
	down_write(&security_rules_lock_lha4);
	key = (ALL_SERVICE & (SEC_RULES_HASH_SZ - 1));
	list_add_tail(&rule->list, &security_rules[key]);
	up_write(&security_rules_lock_lha4);
	return 0;
}

/* 
                                                                         
                                        
                                                            
                                                              
  
                                                            
  
                                                                           
                  
 */
void *msm_ipc_get_security_rule(uint32_t service_id, uint32_t instance_id)
{
	int key;
	struct security_rule *rule;

	key = (service_id & (SEC_RULES_HASH_SZ - 1));
	down_read(&security_rules_lock_lha4);
	/*                                                              */
	list_for_each_entry(rule, &security_rules[key], list) {
		if ((rule->service_id == service_id) &&
		    (rule->instance_id == instance_id)) {
			up_read(&security_rules_lock_lha4);
			return (void *)rule;
		}
	}

	/*                                                   */
	list_for_each_entry(rule, &security_rules[key], list) {
		if ((rule->service_id == service_id) &&
		    (rule->instance_id == ALL_INSTANCE)) {
			up_read(&security_rules_lock_lha4);
			return (void *)rule;
		}
	}

	/*                                                            */
	key = (ALL_SERVICE & (SEC_RULES_HASH_SZ - 1));
	list_for_each_entry(rule, &security_rules[key], list) {
		if ((rule->service_id == ALL_SERVICE) &&
		    (rule->instance_id == ALL_INSTANCE)) {
			up_read(&security_rules_lock_lha4);
			return (void *)rule;
		}
	}
	up_read(&security_rules_lock_lha4);
	return NULL;
}
EXPORT_SYMBOL(msm_ipc_get_security_rule);

/* 
                                                                     
                                                                           
                                      
  
                                                            
  
                                                                      
                                                                      
                                                                      
 */
int msm_ipc_check_send_permissions(void *data)
{
	int i;
	struct security_rule *rule = (struct security_rule *)data;

	/*                            */
	if (!current_euid())
		return 1;

	/*                                                      */
	if (!rule)
		return 1;

	for (i = 0; i < rule->num_group_info; i++) {
		if (in_egroup_p(rule->group_id[i]))
			return 1;
	}
	return 0;
}
EXPORT_SYMBOL(msm_ipc_check_send_permissions);

/* 
                                                                         
  
                                           
 */
int msm_ipc_router_security_init(void)
{
	int i;

	for (i = 0; i < SEC_RULES_HASH_SZ; i++)
		INIT_LIST_HEAD(&security_rules[i]);

	msm_ipc_add_default_rule();
	return 0;
}
EXPORT_SYMBOL(msm_ipc_router_security_init);
