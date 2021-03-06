/* Christopher Feener
 * Fluff.c
 * TODO Test in shrink_page_list tomorrow!
 * This tests page descriptor to virtual address.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/rmap.h>	//For anon_vma... functions.

int init_module(void)
{
	//TODO Find physical address, then divide by PAGE_SIZE for page descr. (Failed; skipped)
	//Or simply start with page descriptor:
	phys_addr_t ptr = 0x400000;
	struct page *p = (struct page *) phys_to_virt(ptr)/*kmalloc(sizeof(struct page), GFP_KERNEL)*/;	//kmalloc is necessary.

	long long int LSB;
	long long int pmapping;
//	long long int p_addr;
//	long long int phys_addr;
	struct anon_vma * VMA;
	struct address_space * File;

	//REVERSE ENGINEERING OF "Find page descriptor".
//	p_addr = (long long int)p;
//	phys_addr = p_addr * PAGE_SIZE;

	//XXX Giving same values for physical and virtual!	
	printk(KERN_ALERT "phys_to_virt(ptr) = %p\np = %p\nvirt_to_phys(p) = %llx\n", phys_to_virt(ptr), p, virt_to_phys(p));

	printk(KERN_ALERT "p->_mapcount: %d\n", atomic_read(&p->_mapcount));

	if ( atomic_read(&p->_mapcount) < 0 ) {
		printk(KERN_ALERT "Error: _mapcount too small.\n");
		return 1;
	}
	//Read *mapping:
	printk(KERN_ALERT "p->mapping = %p\n", p->mapping);
	LSB = ((unsigned long)p->mapping) & 1;
	if ( LSB == 1 ) {
		printk(KERN_ALERT "VMA");
		pmapping = ((unsigned long)p->mapping) >> 1;	//mask low bit
		VMA = (struct anon_vma *)pmapping;	//Set address.
		printk(KERN_ALERT " address = %llx, lowest bit = %llx", pmapping, LSB);
	} else {
		printk(KERN_ALERT "File (or device)");
		pmapping = ((unsigned long)p->mapping);	//mask low bit
		File = (void *)pmapping;
		printk(KERN_ALERT " address = %llx, lowest bit = %llx", pmapping, LSB);
	}


	return 0;
}

void cleanup_module(void){
	printk(KERN_ALERT "Cleaning up.\n");
}
