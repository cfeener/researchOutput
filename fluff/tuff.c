/* Christopher Feener
 * This is a test for phys addr - to - virtual addr lookups.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/rmap.h>	//For anon... functions.

int init_module(void)
{
	//Start with a physical address:
	void * phys_addr = (void *) 0x10000;

	void * user;
	long long int LSB;
	long long int page_mapping;
	long long int page_index_addr; void * page_index;

	//Find page descriptor.
//	page_index_addr = (long long int)phys_addr / PAGE_SIZE;	//PAGE_SIZE may be 4096, or 4k.
//	page_index = (void *)p_index_addr;
	
	printk(KERN_ALERT "p = %p\n", p);

	printk(KERN_ALERT "p->_mapcount: %d\n", atomic_read(&p->_mapcount));

	if ( atomic_read(&p->_mapcount) < 0 ) {
		printk(KERN_ALERT "Error: _mapcount too small.\n");
		return 1;
	}
	//Read *mapping:
	printk(KERN_ALERT "p->mapping = %p\n", p->mapping);
	LSB = ((unsigned long)p->mapping) & 1;
	pmapping = ((unsigned long)p->mapping) >> 1;	//mask low bit
	printk(KERN_ALERT "Address = %llx, lowest bit = %llx", pmapping, LSB);

	file = (void *)pmapping;	//Set address.
	printk(KERN_ALERT "File = %p\n", file);

	return 0;
}

void cleanup_module(void){
	printk(KERN_ALERT "Cleaning up.\n");
}
