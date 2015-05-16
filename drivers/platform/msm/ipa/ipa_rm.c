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

#include <linux/slab.h>
#include <linux/workqueue.h>
#include <mach/ipa.h>
#include "ipa_i.h"
#include "ipa_rm_dependency_graph.h"
#include "ipa_rm_i.h"
#include "ipa_rm_resource.h"

struct ipa_rm_context_type {
	struct ipa_rm_dep_graph *dep_graph;
	struct workqueue_struct *ipa_rm_wq;
	rwlock_t lock;
};
static struct ipa_rm_context_type *ipa_rm_ctx;

/* 
                                             
                                         
                                               
  
                                             
  
                                                                             
                                                        
                          
  
 */
int ipa_rm_create_resource(struct ipa_rm_create_params *create_params)
{
	struct ipa_rm_resource *resource;
	int result;

	if (!create_params)
		return -EINVAL;
	write_lock(&ipa_rm_ctx->lock);
	if (ipa_rm_dep_graph_get_resource(ipa_rm_ctx->dep_graph,
					  create_params->name,
					  &resource) == 0) {
		result = -EEXIST;
		goto bail;
	}
	result = ipa_rm_resource_create(create_params,
			&resource);
	if (result)
		goto bail;
	result = ipa_rm_dep_graph_add(ipa_rm_ctx->dep_graph, resource);
	if (result)
		ipa_rm_resource_delete(resource);
bail:
	write_unlock(&ipa_rm_ctx->lock);
	return result;
}
EXPORT_SYMBOL(ipa_rm_create_resource);

/* 
                                             
                                                 
  
                                             
  
                                                                         
  
 */
int ipa_rm_delete_resource(enum ipa_rm_resource_name resource_name)
{
	struct ipa_rm_resource *resource;
	int result;

	IPADBG("IPA RM ::ipa_rm_delete_resource num[%d] ENTER\n",
			resource_name);
	write_lock(&ipa_rm_ctx->lock);
	if (ipa_rm_dep_graph_get_resource(ipa_rm_ctx->dep_graph,
					resource_name,
						&resource) != 0) {
		IPADBG("ipa_rm_delete_resource param are bad********\n");
		result = -EINVAL;
		goto bail;
	}
	result = ipa_rm_resource_delete(resource);
	if (result) {
		IPADBG("error in ipa_rm_resource_delete\n");
		goto bail;
	}
	result = ipa_rm_dep_graph_remove(ipa_rm_ctx->dep_graph,
								resource_name);
	IPADBG("IPA RM ::ipa_rm_delete_resource [%d] SUCCESS\n",
								resource_name);
bail:
	write_unlock(&ipa_rm_ctx->lock);
	return result;
}
EXPORT_SYMBOL(ipa_rm_delete_resource);

/* 
                                              
                          
                                             
                                           
  
                                             
  
                                                          
                                        
 */
int ipa_rm_add_dependency(enum ipa_rm_resource_name resource_name,
			enum ipa_rm_resource_name depends_on_name)
{
	int result;

	write_lock(&ipa_rm_ctx->lock);
	result = ipa_rm_dep_graph_add_dependency(
						ipa_rm_ctx->dep_graph,
						resource_name,
						depends_on_name);
	write_unlock(&ipa_rm_ctx->lock);
	return result;
}
EXPORT_SYMBOL(ipa_rm_add_dependency);


/* 
                                                 
                          
                                             
                                           
  
                                             
  
                                                          
                                        
 */
int ipa_rm_delete_dependency(enum ipa_rm_resource_name resource_name,
			enum ipa_rm_resource_name depends_on_name)
{
	int result;
	write_lock(&ipa_rm_ctx->lock);
	result = ipa_rm_dep_graph_delete_dependency(
			  ipa_rm_ctx->dep_graph,
			  resource_name,
			  depends_on_name);
	write_unlock(&ipa_rm_ctx->lock);
	return result;
}
EXPORT_SYMBOL(ipa_rm_delete_dependency);

/* 
                                               
                                                      
  
                                             
  
                                                                   
                                              
 */
int ipa_rm_request_resource(enum ipa_rm_resource_name resource_name)
{
	struct ipa_rm_resource *resource;
	int result;
	IPADBG("IPA RM ::ipa_rm_request_resource ENTER\n");

	if (!IPA_RM_RESORCE_IS_PROD(resource_name))
			return -EINVAL;
	read_lock(&ipa_rm_ctx->lock);
	if (ipa_rm_dep_graph_get_resource(ipa_rm_ctx->dep_graph,
			resource_name,
			&resource) != 0) {
		result = -EPERM;
		goto bail;
	}
	result = ipa_rm_resource_producer_request(
			(struct ipa_rm_resource_prod *)resource);

bail:
	IPADBG("IPA RM ::ipa_rm_request_resource EXIT [%d]\n", result);

	read_unlock(&ipa_rm_ctx->lock);
	return result;
}
EXPORT_SYMBOL(ipa_rm_request_resource);

/* 
                                               
                                                      
  
                                             
  
                                                                    
                                              
 */
int ipa_rm_release_resource(enum ipa_rm_resource_name resource_name)
{
	struct ipa_rm_resource *resource;
	int result;
	IPADBG("IPA RM ::ipa_rm_release_resource ENTER\n");

	if (!IPA_RM_RESORCE_IS_PROD(resource_name))
		return -EINVAL;
	read_lock(&ipa_rm_ctx->lock);
	if (ipa_rm_dep_graph_get_resource(ipa_rm_ctx->dep_graph,
					  resource_name,
					  &resource) != 0) {
		result = -EPERM;
		goto bail;
	}
	result = ipa_rm_resource_producer_release(
		    (struct ipa_rm_resource_prod *)resource);

bail:
	IPADBG("IPA RM ::ipa_rm_release_resource EXIT [%d]\n", result);
	read_unlock(&ipa_rm_ctx->lock);
	return result;
}
EXPORT_SYMBOL(ipa_rm_release_resource);

/* 
                                         
                                
                                            
  
                                             
  
                                                           
                                                  
 */
int ipa_rm_register(enum ipa_rm_resource_name resource_name,
			struct ipa_rm_register_params *reg_params)
{
	int result;
	struct ipa_rm_resource *resource;

	if (!IPA_RM_RESORCE_IS_PROD(resource_name))
		return -EINVAL;
	read_lock(&ipa_rm_ctx->lock);
	if (ipa_rm_dep_graph_get_resource(ipa_rm_ctx->dep_graph,
				resource_name,
				&resource) != 0) {
		result = -EPERM;
		goto bail;
	}
	result = ipa_rm_resource_producer_register(
			(struct ipa_rm_resource_prod *)resource,
			reg_params,
			true);
bail:
	read_unlock(&ipa_rm_ctx->lock);
	return result;
}
EXPORT_SYMBOL(ipa_rm_register);

/* 
                                                
                                
                                            
  
                                             
  
                                                           
                                          
 */
int ipa_rm_deregister(enum ipa_rm_resource_name resource_name,
			struct ipa_rm_register_params *reg_params)
{
	int result;
	struct ipa_rm_resource *resource;

	if (!IPA_RM_RESORCE_IS_PROD(resource_name))
		return -EINVAL;
	read_lock(&ipa_rm_ctx->lock);
	if (ipa_rm_dep_graph_get_resource(ipa_rm_ctx->dep_graph,
			resource_name,
			&resource) != 0) {
		result = -EPERM;
		goto bail;
	}
	result = ipa_rm_resource_producer_deregister(
			(struct ipa_rm_resource_prod *)resource,
			reg_params);
bail:
	read_unlock(&ipa_rm_ctx->lock);
	return result;
}
EXPORT_SYMBOL(ipa_rm_deregister);

/* 
                               
                                   
                                                 
             
                         
                                
  
                                             
 */
int ipa_rm_notify_completion(enum ipa_rm_event event,
		enum ipa_rm_resource_name resource_name)
{
	int result;
	if (!IPA_RM_RESORCE_IS_CONS(resource_name)) {
		result = -EINVAL;
		goto bail;
	}
	ipa_rm_wq_send_cmd(IPA_RM_WQ_RESOURCE_CB,
			resource_name,
			event,
			false);
	result = 0;
bail:
	return result;
}
EXPORT_SYMBOL(ipa_rm_notify_completion);

static void ipa_rm_wq_handler(struct work_struct *work)
{
	struct ipa_rm_resource *resource;
	struct ipa_rm_wq_work_type *ipa_rm_work =
			container_of(work,
					struct ipa_rm_wq_work_type,
					work);
	switch (ipa_rm_work->wq_cmd) {
	case IPA_RM_WQ_NOTIFY_PROD:
		if (!IPA_RM_RESORCE_IS_PROD(ipa_rm_work->resource_name))
			return;
		read_lock(&ipa_rm_ctx->lock);
		if (ipa_rm_dep_graph_get_resource(ipa_rm_ctx->dep_graph,
						ipa_rm_work->resource_name,
						&resource) != 0){
			read_unlock(&ipa_rm_ctx->lock);
			return;
		}
		ipa_rm_resource_producer_notify_clients(
				(struct ipa_rm_resource_prod *)resource,
				ipa_rm_work->event,
				ipa_rm_work->notify_registered_only);
		read_unlock(&ipa_rm_ctx->lock);
		break;
	case IPA_RM_WQ_NOTIFY_CONS:
		break;
	case IPA_RM_WQ_RESOURCE_CB:
		read_lock(&ipa_rm_ctx->lock);
		if (ipa_rm_dep_graph_get_resource(ipa_rm_ctx->dep_graph,
						ipa_rm_work->resource_name,
						&resource) != 0){
			read_unlock(&ipa_rm_ctx->lock);
			return;
		}
		ipa_rm_resource_consumer_handle_cb(
				(struct ipa_rm_resource_cons *)resource,
				ipa_rm_work->event);
		read_unlock(&ipa_rm_ctx->lock);
		break;
	default:
		break;
	}

	kfree((void *) work);
}

/* 
                                                          
                                           
                                                               
                                                             
                    
  
                                            
 */
int ipa_rm_wq_send_cmd(enum ipa_rm_wq_cmd wq_cmd,
		enum ipa_rm_resource_name resource_name,
		enum ipa_rm_event event,
		bool notify_registered_only)
{
	int result = -ENOMEM;
	struct ipa_rm_wq_work_type *work = kzalloc(sizeof(*work), GFP_KERNEL);
	if (work) {
		INIT_WORK((struct work_struct *)work, ipa_rm_wq_handler);
		work->wq_cmd = wq_cmd;
		work->resource_name = resource_name;
		work->event = event;
		work->notify_registered_only = notify_registered_only;
		result = queue_work(ipa_rm_ctx->ipa_rm_wq,
				(struct work_struct *)work);
	}
	return result;
}

/* 
                                                    
  
                                            
 */
int ipa_rm_initialize(void)
{
	int result;

	ipa_rm_ctx = kzalloc(sizeof(*ipa_rm_ctx), GFP_KERNEL);
	if (!ipa_rm_ctx) {
		result = -ENOMEM;
		goto bail;
	}
	ipa_rm_ctx->ipa_rm_wq = create_singlethread_workqueue("ipa_rm_wq");
	if (!ipa_rm_ctx->ipa_rm_wq) {
		result = -ENOMEM;
		goto create_wq_fail;
	}
	result = ipa_rm_dep_graph_create(&(ipa_rm_ctx->dep_graph));
	if (result)
		goto graph_alloc_fail;
	rwlock_init(&ipa_rm_ctx->lock);
	IPADBG("IPA RM ipa_rm_initialize SUCCESS\n");
	return 0;

graph_alloc_fail:
	destroy_workqueue(ipa_rm_ctx->ipa_rm_wq);
create_wq_fail:
	kfree(ipa_rm_ctx);
bail:
	return result;
}

/* 
                                
                                         
                              
                                                                
  
                                                             
                                                
 */

int ipa_rm_stat(char *buf, int size)
{
	int i, cnt = 0, result = EINVAL;
	struct ipa_rm_resource *resource = NULL;

	if (!buf || size < 0)
		goto bail;

	read_lock(&ipa_rm_ctx->lock);
	for (i = 0; i < IPA_RM_RESOURCE_PROD_MAX; ++i) {
		result = ipa_rm_dep_graph_get_resource(
				ipa_rm_ctx->dep_graph,
				i,
				&resource);
		if (!result) {
			result = ipa_rm_resource_producer_print_stat(
							resource, buf + cnt,
							size-cnt);
			if (result < 0)
				goto bail;
			cnt += result;
		}
	}
	result = cnt;

bail:
	read_unlock(&ipa_rm_ctx->lock);
	return result;
}

/* 
                                            
 */
void ipa_rm_exit(void)
{
	ipa_rm_dep_graph_delete(ipa_rm_ctx->dep_graph);
	destroy_workqueue(ipa_rm_ctx->ipa_rm_wq);
	kfree(ipa_rm_ctx);
	ipa_rm_ctx = NULL;
}
