#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("cop4610t");
MODULE_DESCRIPTION("A simple Linux kernel module to check systemcalls.");
MODULE_VERSION("0.1");

int open_bar(void);
int bar_group_arrive(int id, int num_customers, int stay_duration, int spending, int waiting_time);
int close_bar(void);

extern int (*STUB_open_bar)(void);
extern int (*STUB_bar_group_arrive)(int,int,int,int,int);
extern int (*STUB_close_bar)(void);

int open_bar(void) {
    printk(KERN_INFO "test_syscall_module: open_bar\n");
    return 0;
}

int bar_group_arrive(int id, int num_customers, int stay_duration, int spending, int waiting_time) {
    printk(KERN_INFO "test_syscall_module: bar_group_arrive\n");
    return 0;
}

int close_bar(void) {
    printk(KERN_INFO "test_syscall_module: close_bar\n");
    return 0;
}

static int __init syscheck_init(void) {
    STUB_open_bar = open_bar;
	STUB_bar_group_arrive = bar_group_arrive;
	STUB_close_bar = close_bar;
    return 0;  // Return 0 to indicate successful loading
}

static void __exit syscheck_exit(void) {
    STUB_open_bar = NULL;
	STUB_bar_group_arrive = NULL;
	STUB_close_bar = NULL;
}

module_init(syscheck_init);  // Specify the initialization function
module_exit(syscheck_exit);  // Specify the exit/cleanup function
