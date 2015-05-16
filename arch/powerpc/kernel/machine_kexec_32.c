/*
 * PPC32 code to handle Linux booting another kernel.
 *
 * Copyright (C) 2002-2003 Eric Biederman  <ebiederm@xmission.com>
 * GameCube/ppc32 port Copyright (C) 2004 Albert Herranz
 * Copyright (C) 2005 IBM Corporation.
 *
 * This source code is licensed under the GNU General Public License,
 * Version 2.  See the file COPYING for more details.
 */

#include <linux/kexec.h>
#include <linux/mm.h>
#include <linux/string.h>
#include <asm/cacheflush.h>
#include <asm/hw_irq.h>
#include <asm/io.h>

typedef void (*relocate_new_kernel_t)(
				unsigned long indirection_page,
				unsigned long reboot_code_buffer,
				unsigned long start_address) __noreturn;

/*
                                                                 
                                       
                                                                     
               
                                                       
 */
void default_machine_kexec(struct kimage *image)
{
	extern const unsigned char relocate_new_kernel[];
	extern const unsigned int relocate_new_kernel_size;
	unsigned long page_list;
	unsigned long reboot_code_buffer, reboot_code_buffer_phys;
	relocate_new_kernel_t rnk;

	/*                                              */
	local_irq_disable();

	/*                                                           
                 */
	machine_kexec_mask_interrupts();

	page_list = image->head;

	/*                                              */
	reboot_code_buffer =
			(unsigned long)page_address(image->control_code_page);
	reboot_code_buffer_phys = virt_to_phys((void *)reboot_code_buffer);

	/*                                                          */
	memcpy((void *)reboot_code_buffer, relocate_new_kernel,
						relocate_new_kernel_size);

	flush_icache_range(reboot_code_buffer,
				reboot_code_buffer + KEXEC_CONTROL_PAGE_SIZE);
	printk(KERN_INFO "Bye!\n");

	/*             */
	rnk = (relocate_new_kernel_t) reboot_code_buffer;
	(*rnk)(page_list, reboot_code_buffer_phys, image->start);
}

int default_machine_kexec_prepare(struct kimage *image)
{
	return 0;
}
