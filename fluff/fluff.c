#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/rmap.h>	//For anon... functions.

static int physToPID(void)
{
	struct page *p = kmalloc(sizeof(struct page));	//Not sure if kmalloc is necessary.

	int p_index;
	p_index = p / PAGE_SIZE;	//PAGE_SIZE may be 4096, or 4k.

	int test = p->mapcount;
}

module_init(physToPID);
module_exit(physToPID);
