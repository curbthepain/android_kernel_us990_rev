/*
 * PCI Backend/Frontend Common Data Structures & Macros
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *   Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 */
#ifndef __XEN_PCI_COMMON_H__
#define __XEN_PCI_COMMON_H__

/*                                                     */
#define XEN_PCI_MAGIC "7"

/*                          */
#define	_XEN_PCIF_active		(0)
#define	XEN_PCIF_active			(1<<_XEN_PCIF_active)
#define	_XEN_PCIB_AERHANDLER		(1)
#define	XEN_PCIB_AERHANDLER		(1<<_XEN_PCIB_AERHANDLER)
#define	_XEN_PCIB_active		(2)
#define	XEN_PCIB_active			(1<<_XEN_PCIB_active)

/*                     */
#define	XEN_PCI_OP_conf_read		(0)
#define	XEN_PCI_OP_conf_write		(1)
#define	XEN_PCI_OP_enable_msi		(2)
#define	XEN_PCI_OP_disable_msi		(3)
#define	XEN_PCI_OP_enable_msix		(4)
#define	XEN_PCI_OP_disable_msix		(5)
#define	XEN_PCI_OP_aer_detected		(6)
#define	XEN_PCI_OP_aer_resume		(7)
#define	XEN_PCI_OP_aer_mmio		(8)
#define	XEN_PCI_OP_aer_slotreset	(9)

/*                          */
#define	XEN_PCI_ERR_success		(0)
#define	XEN_PCI_ERR_dev_not_found	(-1)
#define	XEN_PCI_ERR_invalid_offset	(-2)
#define	XEN_PCI_ERR_access_denied	(-3)
#define	XEN_PCI_ERR_not_implemented	(-4)
/*                                                                  */
#define XEN_PCI_ERR_op_failed		(-5)

/*
                                                                               
                        
 */
#define SH_INFO_MAX_VEC			128

struct xen_msix_entry {
	uint16_t vector;
	uint16_t entry;
};
struct xen_pci_op {
	/*                                          */
	uint32_t cmd;

	/*                                                         */
	int32_t err;

	/*                           */
	uint32_t domain; /*                    */
	uint32_t bus;
	uint32_t devfn;

	/*                                            */
	int32_t offset;
	int32_t size;

	/*                                                                */
	uint32_t value;
	/*                                             */
	uint32_t info;
	/*                     */
	struct xen_msix_entry msix_entries[SH_INFO_MAX_VEC];
};

/*                          */
struct xen_pcie_aer_op {
	/*                                          */
	uint32_t cmd;
	/*                                                                   */
	int32_t err;

	/*                           */
	uint32_t domain; /*                   */
	uint32_t bus;
	uint32_t devfn;
};
struct xen_pci_sharedinfo {
	/*                    */
	uint32_t flags;
	struct xen_pci_op op;
	struct xen_pcie_aer_op aer_op;
};

#endif /*                      */
