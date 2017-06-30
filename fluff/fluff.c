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
	struct page *p = kmalloc(sizeof(struct page), GFP_KERNEL);	//Not sure if kmalloc is necessary.

	void * anon_vma;
	long long int p_m;
	long long int p_index;
	p_index = (long long int)p / PAGE_SIZE;	//PAGE_SIZE may be 4096, or 4k.
	printk(KERN_ALERT "p = %p\nPAGE_SIZE = %lu\np_index = %llx\n", p, PAGE_SIZE, p_index);

	printk(KERN_ALERT "Atomic p->_mapcount: %d\n", atomic_read(&p->_mapcount));

	if ( atomic_read(&p->_mapcount) < 0 ) {
		printk(KERN_ALERT "Error: _mapcount too small.\n");
		return 1;
	}
	//Read *mapping:
	printk(KERN_ALERT "p->mapping = %p\n", p->mapping);
	p_m = ((unsigned long)p->mapping) >> 1;	//mask low bit
	printk(KERN_ALERT "masked out lower bit = %llx\n", p_m);

	anon_vma = (void *)p_m;	//Set address.

	return 0;
}

void cleanup_module(void){
	printk(KERN_ALERT "Cleaning up.\n");
}
