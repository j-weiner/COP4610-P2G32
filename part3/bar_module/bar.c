#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include "bar.h"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Group 32");
MODULE_DESCRIPTION("A simple Linux kernel module for bar management");
MODULE_VERSION("0.1");

struct mutex bar_lock;
Waiting_list *lobby;
bool bar_open = false;
int tables[TABLES][STOOLS_PER_TABLE];
struct server_status servers[1];
unsigned long groups_served = 0;
unsigned long customers_served = 0;
unsigned long groups_left = 0;
int profit = 0;
int rating_total = 0;
int rating_count = 0;
struct proc_dir_entry* bar_entry;

int open_bar(void) {
    mutex_lock(&bar_lock);
    bar_open = true;
    mutex_unlock(&bar_lock);
    return 0;
}

int bar_group_arrive(int id, int num_customers, int stay_duration, int spending, int waiting_time) {
    return add_group(id, num_customers, stay_duration, spending, waiting_time, lobby);
}

int close_bar(void) {
    mutex_lock(&bar_lock);
    bar_open = false;
    mutex_unlock(&bar_lock);
    return 0;
}

int add_group(int group_id, int customers, int stay_time, int spending, int wait_time, Waiting_list* input_list) {
    Waiting_list *new = kmalloc(sizeof(Waiting_list), GFP_KERNEL);
    if (!new) return -ENOMEM;

    new->group_id = group_id;
    new->customers = customers;
    new->stay_time = stay_time;
    new->spending = spending;
    new->wait_time = wait_time;
    
    INIT_LIST_HEAD(&new->list);
    list_add_tail(&new->list, &input_list->list);
    return 0;
}

static int __init syscheck_init(void) {
    mutex_init(&bar_lock);
    mutex_lock(&bar_lock);

    memset(tables, 0, sizeof(tables));
    for (int i = 0; i < ARRAY_SIZE(servers); i++) {
        servers[i].current_state = 0;
    }

    lobby = kmalloc(sizeof(Waiting_list), GFP_KERNEL);
    if (!lobby) {
        mutex_unlock(&bar_lock);
        return -ENOMEM;
    }
    INIT_LIST_HEAD(&lobby->list);

    mutex_unlock(&bar_lock);

    bar_entry = proc_create(ENTRY_NAME, PERMS, PARENT, &bar_proc_fops);
    if (!bar_entry) {
        kfree(lobby);
        return -ENOMEM;
    }

    STUB_open_bar = open_bar;
    STUB_bar_group_arrive = bar_group_arrive;
    STUB_close_bar = close_bar;
    return 0;
}

static void __exit syscheck_exit(void) {
    mutex_lock(&bar_lock);

    Waiting_list *entry, *tmp;
    list_for_each_entry_safe(entry, tmp, &lobby->list, list) {
        list_del(&entry->list);
        kfree(entry);
    }

    if (bar_entry) remove_proc_entry(ENTRY_NAME, PARENT);
    kfree(lobby);

    mutex_unlock(&bar_lock);
    mutex_destroy(&bar_lock);

    STUB_open_bar = NULL;
    STUB_bar_group_arrive = NULL;
    STUB_close_bar = NULL;
}

module_init(syscheck_init);
module_exit(syscheck_exit);