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
int readMaps(void) //From https://www.howtoforge.com/reading-files-from-the-linux-kernel-space-module-driver-fedora-14
{
    // Create variables
    struct file *f;
    char buf[128];
    mm_segment_t fs;
    int i;
    // Init the buffer with 0
    for(i=0;i<128;i++)
        buf[i] = 0;
    // To see in /var/log/messages that the module is operating
    printk(KERN_INFO "My module is loaded\n");
    // Obviously it is much smaller than the 128 bytes, but hell with it =)
    f = filp_open("/proc/9643/maps", O_RDONLY, 0);	//XXX Changed for CF's purposes.
    if(f == NULL)
        printk(KERN_ALERT "filp_open error!!.\n");
    else{
        // Get current segment descriptor
        fs = get_fs();
        // Set segment descriptor associated to kernel space
        set_fs(get_ds());
        // Read the file
        f->f_op->read(f, buf, 128, &f->f_pos);
        // Restore segment descriptor
        set_fs(fs);
        // See what we read from file
        printk(KERN_INFO "buf:%s\n",buf);
    }
    filp_close(f,NULL);
    return 0;
}

module_init(readMaps);
module_exit(readMaps);
*/
// Virt_to_phys works perfectly, but of little use currently.
static int vm_mem_test_init(void)	//From https://www.spinics.net/lists/newbies/msg53705.html
{

	void *km;
	km = 0xbbc000;	//Virtual address of qemu bash at 2 pm, 6/28/2017. Change as necessary.

	printk(KERN_ALERT "vm mem test init\n");

//	km = kmalloc(1,GFP_KERNEL);

	if(km == NULL) {
		printk(KERN_ALERT "Could not kmalloc\n");
		return -1;
	} else {
//		printk(KERN_ALERT "Allocated\n");
		printk(KERN_ALERT "Virtual addr : %x\n",(unsigned int)km);
		printk(KERN_ALERT "Kernel physical addr : 0x%x\n",virt_to_phys(km));	//Here is the core concept!
//		kfree(km);
	}

	return 0;

}

module_init(vm_mem_test_init);
module_exit(vm_mem_test_init);

