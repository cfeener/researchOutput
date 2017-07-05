/* Christopher Feener
 * Tuff.c
 * This is a test for phys addr - to - virtual addr lookups. 
 * It attempts to follow the directions from the site 
 * This is an algorithm of taking an arbitrary physical address,
 * dividing it up, and type casting.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/rmap.h>	//For anon... functions.

int init_module(void)
{
	//Start with a physical address:
	phys_addr_t phys_addr;
	phys_addr_t addend1 = 0xffff880000000000;
	phys_addr_t addend2 = 0x10000;
	phys_addr = addend1 + addend2;
	void * ptr = (void *)phys_addr;
	printk(KERN_ALERT "phys_addr = %p\nvirt_addr = %p\n", ptr, (void *)phys_to_virt(phys_addr));

	long long int page_index_addr; 
	struct page * page_index;
	long long int LSB;
	long long int page_mapping;
	void * user;

	//Find page descriptor.
	page_index_addr = (long long int)addend2 / PAGE_SIZE + (long long int)addend1;	//PAGE_SIZE may be 4096, or 4k.
	page_index = (struct page *)page_index_addr;
	
	printk(KERN_ALERT "page descriptor index = %p\n", page_index);

	printk(KERN_ALERT "page_index->_mapcount: %d\n", atomic_read(&page_index->_mapcount));

	if ( atomic_read(&page_index->_mapcount) < 0 ) {
		printk(KERN_ALERT "Error: _mapcount too small.\n");
		return 1;
	}
/*	//XXX ERROR: _mapcount is giving incorrect values.
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
