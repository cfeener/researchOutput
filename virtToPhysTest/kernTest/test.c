#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/gfp.h>
#include <linux/types.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/slab.h>

static int vm_mem_test_init(void)
{

    void *km;

    printk(KERN_ALERT "vm mem test init\n");

    km = kmalloc(1,GFP_KERNEL);

    if(km == NULL) {
        printk(KERN_ALERT "Could not kmalloc\n");
        return -1;
    } else {
        printk(KERN_ALERT "Allocated\n");
        printk(KERN_ALERT "Virtual addr : %x\n",(unsigned int)km);
        printk(KERN_ALERT "Kernel physical addr : 0x%x\n",virt_to_phys(km));
        kfree(km);
    }

  return 0;

}

module_init(vm_mem_test_init);
module_exit(vm_mem_test_init);
