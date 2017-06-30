#include <linux/init.h>
#include <linux/kernel.h>	//For kernel info
#include <linux/printk.h>
#include <linux/module.h>	//For all modules.
#include <linux/gfp.h>
#include <linux/types.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/slab.h>

#include <linux/fs.h>	//For filp
#include <asm/uaccess.h>	//For segment descriptors.

#include <linux/syscalls.h>
#include <linux/fcntl.h>

//See also http://www.linuxjournal.com/node/8110/print
/*
//See https://www.howtoforge.com/reading-files-from-the-linux-kernel-space-module-driver-fedora-14
*/
// Virt_to_phys works perfectly, but of little use currently.
static int vm_mem_test_init(void)	//From https://www.spinics.net/lists/newbies/msg53705.html
{

	void *km;
//	km = 0xbbc000;	//Virtual address of qemu bash at 2 pm, 6/28/2017. Change as necessary.

	printk(KERN_ALERT "vm mem test init\n");

	km = kmalloc(1,GFP_KERNEL);

	if(km == NULL) {
		printk(KERN_ALERT "Could not kmalloc\n");
		return -1;
	} else {
		printk(KERN_ALERT "Allocated\n");
		printk(KERN_ALERT "Virtual addr : %x\n",(unsigned int)km);
		printk(KERN_ALERT "Kernel physical addr : 0x%x\n",virt_to_phys(km));	//Here is the core concept!
		kfree(km);
	}

	return 0;

}

module_init(vm_mem_test_init);
module_exit(vm_mem_test_init);

