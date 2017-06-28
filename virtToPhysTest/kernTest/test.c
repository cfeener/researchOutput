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


static int virtToPhys(void)
{
	int fd;
	//From http://www.linuxjournal.com/node/8110/print
	fd = sys_open("/proc/9643/maps", O_RDONLY, 0);
	if (fd >=0) {
		

		sys_close(fd);
	}

	return 0;
}

module_init(virtToPhys);
module_exit(virtToPhys);
/*
int init_module(void) //From https://www.howtoforge.com/reading-files-from-the-linux-kernel-space-module-driver-fedora-14
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
    // I am using Fedora and for the test I have chosen following file
    // Obviously it is much smaller than the 128 bytes, but hell with it =)
    f = filp_open("/proc/9643/maps", O_RDONLY, 0);	//XXX get_fs may be for something else.
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

void cleanup_module(void)
{
    printk(KERN_INFO "My module is unloaded\n");
}
*/
/*
static int vm_mem_test_init(void)	//From https://www.spinics.net/lists/newbies/msg53705.html
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
        printk(KERN_ALERT "Kernel physical addr : 0x%x\n",virt_to_phys(km));	//Here is the core concept!
        kfree(km);
    }

  return 0;

}

module_init(vm_mem_test_init);
module_exit(vm_mem_test_init);
*/
