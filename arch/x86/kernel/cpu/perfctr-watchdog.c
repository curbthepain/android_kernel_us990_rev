/*
                                                  
  
                                                                              
                                    
  
                                                                            
                                      
  
                                                 
  
 */

#include <linux/percpu.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/bitops.h>
#include <linux/smp.h>
#include <asm/nmi.h>
#include <linux/kprobes.h>

#include <asm/apic.h>
#include <asm/perf_event.h>

/*
                                                                            
                                
  
                                                 
 */
#define NMI_MAX_COUNTER_BITS 66

/*
                                                                   
                                                               
                                                                        
                                                                          
                    
 */
static DECLARE_BITMAP(perfctr_nmi_owner, NMI_MAX_COUNTER_BITS);
static DECLARE_BITMAP(evntsel_nmi_owner, NMI_MAX_COUNTER_BITS);

/*                                                   */
static inline unsigned int nmi_perfctr_msr_to_bit(unsigned int msr)
{
	/*                                                            */
	switch (boot_cpu_data.x86_vendor) {
	case X86_VENDOR_AMD:
		if (msr >= MSR_F15H_PERF_CTR)
			return (msr - MSR_F15H_PERF_CTR) >> 1;
		return msr - MSR_K7_PERFCTR0;
	case X86_VENDOR_INTEL:
		if (cpu_has(&boot_cpu_data, X86_FEATURE_ARCH_PERFMON))
			return msr - MSR_ARCH_PERFMON_PERFCTR0;

		switch (boot_cpu_data.x86) {
		case 6:
			return msr - MSR_P6_PERFCTR0;
		case 15:
			return msr - MSR_P4_BPU_PERFCTR0;
		}
	}
	return 0;
}

/*
                                                    
                                                         
 */
static inline unsigned int nmi_evntsel_msr_to_bit(unsigned int msr)
{
	/*                                                        */
	switch (boot_cpu_data.x86_vendor) {
	case X86_VENDOR_AMD:
		if (msr >= MSR_F15H_PERF_CTL)
			return (msr - MSR_F15H_PERF_CTL) >> 1;
		return msr - MSR_K7_EVNTSEL0;
	case X86_VENDOR_INTEL:
		if (cpu_has(&boot_cpu_data, X86_FEATURE_ARCH_PERFMON))
			return msr - MSR_ARCH_PERFMON_EVENTSEL0;

		switch (boot_cpu_data.x86) {
		case 6:
			return msr - MSR_P6_EVNTSEL0;
		case 15:
			return msr - MSR_P4_BSU_ESCR0;
		}
	}
	return 0;

}

/*                                                   */
int avail_to_resrv_perfctr_nmi_bit(unsigned int counter)
{
	BUG_ON(counter > NMI_MAX_COUNTER_BITS);

	return !test_bit(counter, perfctr_nmi_owner);
}
EXPORT_SYMBOL(avail_to_resrv_perfctr_nmi_bit);

int reserve_perfctr_nmi(unsigned int msr)
{
	unsigned int counter;

	counter = nmi_perfctr_msr_to_bit(msr);
	/*                                        */
	if (counter > NMI_MAX_COUNTER_BITS)
		return 1;

	if (!test_and_set_bit(counter, perfctr_nmi_owner))
		return 1;
	return 0;
}
EXPORT_SYMBOL(reserve_perfctr_nmi);

void release_perfctr_nmi(unsigned int msr)
{
	unsigned int counter;

	counter = nmi_perfctr_msr_to_bit(msr);
	/*                                        */
	if (counter > NMI_MAX_COUNTER_BITS)
		return;

	clear_bit(counter, perfctr_nmi_owner);
}
EXPORT_SYMBOL(release_perfctr_nmi);

int reserve_evntsel_nmi(unsigned int msr)
{
	unsigned int counter;

	counter = nmi_evntsel_msr_to_bit(msr);
	/*                                        */
	if (counter > NMI_MAX_COUNTER_BITS)
		return 1;

	if (!test_and_set_bit(counter, evntsel_nmi_owner))
		return 1;
	return 0;
}
EXPORT_SYMBOL(reserve_evntsel_nmi);

void release_evntsel_nmi(unsigned int msr)
{
	unsigned int counter;

	counter = nmi_evntsel_msr_to_bit(msr);
	/*                                        */
	if (counter > NMI_MAX_COUNTER_BITS)
		return;

	clear_bit(counter, evntsel_nmi_owner);
}
EXPORT_SYMBOL(release_evntsel_nmi);
