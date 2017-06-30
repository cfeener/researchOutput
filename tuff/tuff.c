/* Christopher Feener
 * Tuff.c
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
	
/*
	long long int page_index_addr; 
	struct page * page_index;
	long long int LSB;
	long long int page_mapping;
	void * user;

	//Find page descriptor.
	page_index_addr = (long long int)phys_addr / PAGE_SIZE;	//PAGE_SIZE may be 4096, or 4k.
	page_index = (struct page *)page_index_addr;
	
	printk(KERN_ALERT "page descriptor index = %p\n", page_index);

	printk(KERN_ALERT "page_index->_mapcount: %d\n", atomic_read(&page_index->_mapcount));

	if ( atomic_read(&page_index->_mapcount) < 0 ) {
		printk(KERN_ALERT "Error: _mapcount too small.\n");
		return 1;
	}
	//Read *mapping:
	printk(KERN_ALERT "page->mapping = %p\n", page_index->mapping);
	LSB = ((unsigned long)page_index->mapping) & 1;
	page_mapping = ((unsigned long)page_index->mapping) >> 1;	//mask low bit
	printk(KERN_ALERT "Address = %llx, lowest bit = %llx", page_mapping, LSB);

	user = (void *)page_mapping;	//Set address.
	printk(KERN_ALERT "File = %p\n", user);
*/
	return 0;
}

void cleanup_module(void){
	printk(KERN_ALERT "Cleaning up.\n");
}