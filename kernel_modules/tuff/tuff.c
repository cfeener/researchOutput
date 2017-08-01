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
	printk(KERN_ALERT "vm_start: %lu\n\n", task->mm->mmap->vm_start);

	//Iterate from current:
	list_for_each(list, &current->children) {
//		task = list_entry(list, struct task_struct, sibling);
//		list_entry(task->list.next	//XXX Continue!
		printk(KERN_ALERT "Name: %s, PID: %d\n\n", task->comm, task->pid);
		printk(KERN_ALERT "vm_start: %lu\n\n", task->mm->mmap->vm_start);
	}

	struct vm_area_struct *vma = task->mm->mmap;
	struct page *page = kmalloc(sizeof(struct page), GFP_KERNEL);
	if (page_address_in_vma(page, vma) == -EFAULT)
		printk(KERN_ALERT "Page is not in VMA.\n");
	else
		printk(KERN_ALERT "Found!\n");

	return 0;
}

void cleanup_module(void){
	printk(KERN_ALERT "Cleaning up.\n");
}
