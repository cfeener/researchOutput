/* Christopher Feener
 * Tuff.c
 * Finished testing iterator for struct task_struct current.
 * Tests current->tsk_struct's->vma. Will focus on page_address_in_vma() from rmap later.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/rmap.h>	//For page_address_in_vma().
#include <linux/sched.h>	//For task_struct's.
#include <linux/list.h>	//For list_for_each.

int init_module(void)
{
	struct list_head *list;
	struct task_struct *task;
	task = current;

	printk(KERN_ALERT "Name: %s, PID: %d", task->comm, task->pid);

//	while (task->pid != 0) {
	list_for_each(list, &current->children) {
		task = list_entry(list, struct task_struct, sibling);
//		task = task->parent; 	//Try child, next, and finally actual iterator.
		printk(KERN_ALERT "Name: %s, PID: %d", task->comm, task->pid);
	}
	//->mm->mmap->anon_vma;

	return 0;
}

void cleanup_module(void){
	printk(KERN_ALERT "Cleaning up.\n");
}
