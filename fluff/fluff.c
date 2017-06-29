#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/rmap.h>	//For anon... functions.

int init_module(void)
{
	struct page *p = kmalloc(sizeof(struct page), GFP_KERNEL);	//Not sure if kmalloc is necessary.

	long long int p_index;
	p_index = (long long int)p / PAGE_SIZE;	//PAGE_SIZE may be 4096, or 4k.
	printk(KERN_ALERT "p = %p\nPAGE_SIZE = %lu\np_index = %llx\n", p, PAGE_SIZE, p_index);

	if ( p->_mapcount > 0)
		printk(KERN_ALERT "YES\n");	//p->_mapcount works!

	return 0;
}

void cleanup_module(void){
	printk(KERN_ALERT "Cleaning up.\n");
}
