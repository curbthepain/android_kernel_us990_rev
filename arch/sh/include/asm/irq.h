#ifndef __ASM_SH_IRQ_H
#define __ASM_SH_IRQ_H

#include <linux/cpumask.h>
#include <asm/machvec.h>

/*
                                                                        
                                                                   
                       
 */
#define NR_IRQS			512
#define NR_IRQS_LEGACY		8	/*                        */

/*
                                                                   
                                                                     
                                                                     
                                          
 */
#define NO_IRQ_IGNORE		((unsigned int)-1)

/*
                               
 */
extern void make_maskreg_irq(unsigned int irq);
extern unsigned short *irq_mask_register;

/*
            
 */
void init_IRQ_pint(void);
void make_imask_irq(unsigned int irq);

static inline int generic_irq_demux(int irq)
{
	return irq;
}

#define irq_demux(irq)		sh_mv.mv_irq_demux(irq)

void init_IRQ(void);
void migrate_irqs(void);

asmlinkage int do_IRQ(unsigned int irq, struct pt_regs *regs);

#ifdef CONFIG_IRQSTACKS
extern void irq_ctx_init(int cpu);
extern void irq_ctx_exit(int cpu);
# define __ARCH_HAS_DO_SOFTIRQ
#else
# define irq_ctx_init(cpu) do { } while (0)
# define irq_ctx_exit(cpu) do { } while (0)
#endif

#ifdef CONFIG_INTC_BALANCING
extern unsigned int irq_lookup(unsigned int irq);
extern void irq_finish(unsigned int irq);
#else
#define irq_lookup(irq)		(irq)
#define irq_finish(irq)		do { } while (0)
#endif

#include <asm-generic/irq.h>
#ifdef CONFIG_CPU_SH5
#include <cpu/irq.h>
#endif

#endif /*                */
