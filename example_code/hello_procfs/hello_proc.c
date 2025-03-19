#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

#define BUF_LEN 100

static char msg[BUF_LEN];
static struct proc_dir_entry* proc_entry;

static ssize_t my_read(struct file* file, char * ubuf, size_t count, loff_t *ppos)
{
	ssize_t procfs_buf_len = 0;

	printk(KERN_INFO "proc_read\n");

	procfs_buf_len = strlen(msg);
	if (*ppos > 0 || count < procfs_buf_len)
		return 0;

	if (copy_to_user(ubuf, msg, procfs_buf_len) != 0)
		return -EFAULT;

	*ppos = procfs_buf_len;
	printk(KERN_INFO "gave to user %s\n", msg);
	return procfs_buf_len;
}


static ssize_t my_write(struct file* file, const char * ubuf, size_t count, loff_t* ppos)
{
	ssize_t procfs_buf_len = 0;
	printk(KERN_INFO "proc_write\n");

	if (count > BUF_LEN)
		procfs_buf_len = BUF_LEN;
	else
		procfs_buf_len = count;

	if (copy_from_user(msg, ubuf, procfs_buf_len) != 0)
		printk(KERN_ERR "copy from user failed\n");
	else
		printk(KERN_INFO "got from user: %s\n", msg);

	return procfs_buf_len;
}


static const struct proc_ops procfile_fops = {
    .proc_read = my_read,
    .proc_write = my_write,
};


static int hello_init(void)
{
	proc_entry = proc_create("hello_proc", 0666, NULL, &procfile_fops);

	if (proc_entry == NULL)
		return -ENOMEM;

	return 0;
}

static void hello_exit(void)
{
	proc_remove(proc_entry);
	return;
}



module_init(hello_init);
module_exit(hello_exit);

