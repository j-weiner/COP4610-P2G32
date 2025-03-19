#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("cop4610");
MODULE_DESCRIPTION("Hello world.");

static int __init hello_init(void) {
	printk(KERN_INFO "Hello, World!\n");
	return 0;
}

static void __exit hello_exit(void) {
	printk(KERN_INFO "Goodbye, sleepy world.\n");
}

module_init(hello_init);
module_exit(hello_exit);
