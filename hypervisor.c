
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/kernel.h>

//to check for VMX support, check if bit 5 in ecx == 1 when cpuid called 

bool vmxSupport(void) {
	int getVmxSupport, vmxBit;

	asm("mov $1, %eax;" 
		"cpuid;"
		"mov %%ecx, %0\n\t"
		: "=r" (getVmxSupport) //output operands 
		: 
		: "%eax", "%ecx"
	);

	vmxBit = (getVmxSupport >> 5) & 1; 
	if (vmxBit == 1) {
		return true; 
	} else {
		return false;        
	}
}


static int __init my_init(void) { 
	bool isVmxSupported = vmxSupport; 
	printk(KERN_INFO "hello world"); 
	printk(KERN_INFO "VMXSUPPORTED %d", isVmxSupported); 
	return 0; 
}

static void __exit my_exit(void) {
	printk(KERN_INFO "goodbye world"); 
}

module_init(my_init); 
module_exit(my_exit);

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Asritha Bodepudi"); 
MODULE_DESCRIPTION("hypervisor"); 
