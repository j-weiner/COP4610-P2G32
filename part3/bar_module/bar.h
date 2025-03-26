#ifndef BAR_H
#define BAR_H

#include "bar_def.h"
#include <linux/list.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mutex.h>

typedef struct server_status {
    struct task_struct *thread;
    int server_state;
    bool stop_thread;
}

typedef struct waiting_list {
    struct list_head list;
    int group_id;
    int customers;
    int stay_time;
    int spending;
    int wait_time;
} Waiting_list;

struct server_status {
    int current_group;
    bool busy;
};

// Global variables (defined in bar.c)

extern struct mutex bar_lock;
extern Waiting_list *lobby;
extern bool bar_open;
extern int tables[TABLES][STOOLS_PER_TABLE];
extern struct server_status servers[1];
extern unsigned long groups_served;
extern unsigned long customers_served;
extern unsigned long groups_left;
extern int profit;
extern int rating_total;
extern int rating_count;
extern struct proc_dir_entry* bar_entry;


// Function prototypes
int open_bar(void);
int bar_group_arrive(int id, int num_customers, int stay_duration, int spending, int waiting_time);
int close_bar(void);
void clean_table(int tableNum);
int add_group(int group_id, int customers, int stay_time, int spending, int wait_time, Waiting_list* input_list);
int bar_proc_show(struct seq_file*, void *);
int bar_proc_open(struct inode*, struct file*);
//int server_thread_fn(void *data);
int find_available_table(int needed_stools);
void occupy_table(int table_idx, int group_id, int customers);

// ProcFS
extern const struct proc_ops bar_proc_fops;

// System call stubs
extern int (*STUB_open_bar)(void);
extern int (*STUB_bar_group_arrive)(int, int, int, int, int);
extern int (*STUB_close_bar)(void);

#endif