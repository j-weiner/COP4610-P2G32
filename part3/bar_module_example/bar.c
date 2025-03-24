#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/timekeeping.h>
#include <linux/mutex.h>
#include "bar_functions.h"

#define ENTRY_NAME "bar"
#define PERMS 0644
#define PARENT NULL
#define tables 4
#define stools_per_table 8

static struct mutex bar_lock;

static bool open = false;
static int groups = 0;
static int customers = 0;
static int left = 0;
static int profit = 0;
static float rating = 0.000


static struct proc_dir_entry* bar_entry

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Group 32");
MODULE_DESCRIPTION("A simple Linux kernel module to check systemcalls.");
MODULE_VERSION("0.1");

int open_bar(void);
int bar_group_arrive(int id, int num_customers, int stay_duration, int spending, int waiting_time);
int close_bar(void);

static ssize_t 

extern int (*STUB_open_bar)(void);
extern int (*STUB_bar_group_arrive)(int,int,int,int,int);
extern int (*STUB_close_bar)(void);

int open_bar(void) {

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

    mutex_init(&bar_lock);
    mutex_lock(&bar_lock);
    mutex_unlock(&bar_lock)

    
    Waiting_list * wait_list;
    wait_list = kmalloc(sizeof(Waiting_list), __GFP_RECLAIM);
    if (!wait_list) { return -ENOMEM;}
    static int bar[tables][stools_per_table]={NULL};
    int server = 0;
    return 0;  // Return 0 to indicate successful loading
}

static void __exit syscheck_exit(void) {
    STUB_open_bar = NULL;
	STUB_bar_group_arrive = NULL;
	STUB_close_bar = NULL;
}

module_init(syscheck_init);  // Specify the initialization function
module_exit(syscheck_exit);  // Specify the exit/cleanup function

int add_group()

