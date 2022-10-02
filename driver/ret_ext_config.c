#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("arotq");
MODULE_DESCRIPTION("Pcie driver");

/* pci_config_init variables */

#define PCI_SATA_CONTROLLER 0x2829
#define CAPABILITY_POINTER_POS 0x34
#define SLOT_STATUS_REGISTER_OFFSET 0x1A
struct pci_dev *dev = NULL;
u8 capability_ptr_addr;
u8 capability_struct_addr;
u32 slot_status_reg_pos;
u16 slot_status_reg_first_byte;

// Check if PCIe space is available on server. 
int pci_config_init(void)
{	
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	
	
	dev = pci_get_device(0x106B, 0x003F, dev);
	printk(KERN_ALERT "***** PCI device details *****\n"
	"VendoID => 0x%x\n""DeviceID => 0x%x", dev->vendor, dev->device);
	
	// pci_read_config_byte(dev, CAPABILITY_POINTER_POS, &capability_ptr_addr);
	
	
	// Get the address of the PCI EXPRESS CAPABILITY STRUCTURE
	capability_struct_addr =  pci_find_capability(dev, PCI_CAP_ID_PM);
	
	pci_read_config_word(dev, capability_struct_addr, &slot_status_reg_first_byte);
	
	//slot_status_reg_pos = capability_ptr_addr + SLOT_STATUS_REGISTER_OFFSET;
	
	//pci_read_config_word(dev, slot_status_reg_pos, &slot_status_reg_first_byte);
	
	printk(KERN_ALERT "The value obtained from power management is 0x%x\n", capability_struct_addr);
	return 0;
}

void pci_config_exit(void)
{
	printk(KERN_ALERT "Exiting the driver\n");
}

module_init(pci_config_init);
module_exit(pci_config_exit);

