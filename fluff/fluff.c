/* Christopher Feener
 * This is a test for phys addr - virtual addr lookups.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/rmap.h>	//For anon... functions.

int init_module(void)
{
	//Find physical address. Or simply start with page descriptor:
	struct page *p = kmalloc(sizeof(struct page), GFP_KERNEL);	//Not sure if kmalloc is necessary.

	void * fileOrProc;
	long long int LSB;
	long long int pmapping;
//	long long int p_index_addr;
//	void * p_index;

	//Find page descriptor.
//	p_index_addr = (long long int)p / PAGE_SIZE;	//PAGE_SIZE may be 4096, or 4k.
//	p_index = (void *)p_index_addr;
	
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

	fileOrProc = (void *)pmapping;	//Set address.

	return 0;
}

void cleanup_module(void){
	printk(KERN_ALERT "Cleaning up.\n");
}
