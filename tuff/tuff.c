/* Christopher Feener
 * Tuff.c
 * Tests current->tsk_struct's->vma. Will focus on page_address_in_vma() from rmap later.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/rmap.h>	//For page_address_in_vma().
#include <linux/sched.h>	//For task_struct's.

int init_module(void)
{
	struct task_struct *temp_curr;
	temp_curr = current;
	//->mm->mmap->anon_vma;

	return 0;
}

void cleanup_module(void){
	printk(KERN_ALERT "Cleaning up.\n");
}
