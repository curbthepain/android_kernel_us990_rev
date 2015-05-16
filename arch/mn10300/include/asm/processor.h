/* MN10300 Processor specifics
 *
 * Copyright (C) 2007 Matsushita Electric Industrial Co., Ltd.
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version
 * 2 of the Licence, or (at your option) any later version.
 */

#ifndef _ASM_PROCESSOR_H
#define _ASM_PROCESSOR_H

#include <linux/threads.h>
#include <linux/thread_info.h>
#include <asm/page.h>
#include <asm/ptrace.h>
#include <asm/cpu-regs.h>
#include <asm/uaccess.h>
#include <asm/current.h>

/*                                        */
struct task_struct;
struct mm_struct;

/*
                                                       
                                           
 */
#define current_text_addr()			\
({						\
	void *__pc;				\
	asm("mov pc,%0" : "=a"(__pc));		\
	__pc;					\
})

extern void get_mem_info(unsigned long *mem_base, unsigned long *mem_size);

extern void show_registers(struct pt_regs *regs);

/*
                                                                  
                                                                      
                              
 */

struct mn10300_cpuinfo {
	int		type;
	unsigned long	loops_per_jiffy;
	char		hard_math;
};

extern struct mn10300_cpuinfo boot_cpu_data;

#ifdef CONFIG_SMP
#if CONFIG_NR_CPUS < 2 || CONFIG_NR_CPUS > 8
# error Sorry, NR_CPUS should be 2 to 8
#endif
extern struct mn10300_cpuinfo cpu_data[];
#define current_cpu_data cpu_data[smp_processor_id()]
#else  /*            */
#define cpu_data &boot_cpu_data
#define current_cpu_data boot_cpu_data
#endif /*            */

extern void identify_cpu(struct mn10300_cpuinfo *);
extern void print_cpu_info(struct mn10300_cpuinfo *);
extern void dodgy_tsc(void);
#define cpu_relax() barrier()

/*
                                             
 */
#define TASK_SIZE		0x70000000

/*
                                              
 */
#define STACK_TOP		0x70000000
#define STACK_TOP_MAX		STACK_TOP

/*                                                                 
                       
 */
#define TASK_UNMAPPED_BASE	0x30000000

struct fpu_state_struct {
	unsigned long	fs[32];		/*               */
	unsigned long	fpcr;		/*                      */
};

struct thread_struct {
	struct pt_regs		*uregs;		/*                          */
	unsigned long		pc;		/*           */
	unsigned long		sp;		/*           */
	unsigned long		a3;		/*           */
	unsigned long		wchan;
	unsigned long		usp;
	unsigned long		fpu_flags;
#define THREAD_USING_FPU	0x00000001	/*                                 */
#define THREAD_HAS_FPU		0x00000002	/*                                       */
	struct fpu_state_struct	fpu_state;
};

#define INIT_THREAD		\
{				\
	.uregs	= init_uregs,	\
	.pc	= 0,		\
	.sp	= 0,		\
	.a3	= 0,		\
	.wchan	= 0,		\
}

#define INIT_MMAP \
{ &init_mm, 0, 0, NULL, PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC, 1, \
  NULL, NULL }

/*
                                                         
                                                                               
                                    
 */
static inline void start_thread(struct pt_regs *regs,
				unsigned long new_pc, unsigned long new_sp)
{
	struct thread_info *ti = current_thread_info();
	struct pt_regs *frame0;

	frame0 = thread_info_to_uregs(ti);
	frame0->epsw = EPSW_nSL | EPSW_IE | EPSW_IM;
	frame0->pc = new_pc;
	frame0->sp = new_sp;
	ti->frame = frame0;
}


/*                                      */
extern void release_thread(struct task_struct *);

/*                                                       */
extern void prepare_to_copy(struct task_struct *tsk);

/*
                                                            
 */
extern int kernel_thread(int (*fn)(void *), void *arg, unsigned long flags);

/*
                                       
 */
extern unsigned long thread_saved_pc(struct task_struct *tsk);

unsigned long get_wchan(struct task_struct *p);

#define task_pt_regs(task) ((task)->thread.uregs)
#define KSTK_EIP(task) (task_pt_regs(task)->pc)
#define KSTK_ESP(task) (task_pt_regs(task)->sp)

#define KSTK_TOP(info)				\
({						\
	(unsigned long)(info) + THREAD_SIZE;	\
})

#define ARCH_HAS_PREFETCH
#define ARCH_HAS_PREFETCHW

static inline void prefetch(const void *x)
{
#ifdef CONFIG_MN10300_CACHE_ENABLED
#ifdef CONFIG_MN10300_PROC_MN103E010
	asm volatile ("nop; nop; dcpf (%0)" : : "r"(x));
#else
	asm volatile ("dcpf (%0)" : : "r"(x));
#endif
#endif
}

static inline void prefetchw(const void *x)
{
#ifdef CONFIG_MN10300_CACHE_ENABLED
#ifdef CONFIG_MN10300_PROC_MN103E010
	asm volatile ("nop; nop; dcpf (%0)" : : "r"(x));
#else
	asm volatile ("dcpf (%0)" : : "r"(x));
#endif
#endif
}

#endif /*                  */