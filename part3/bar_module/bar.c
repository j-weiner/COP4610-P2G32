#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/timekeeping.h>
#include <linux/mutex.h>
#include <linux/seq_file.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Group 32");
MODULE_DESCRIPTION("A simple Linux kernel module for bar management");
MODULE_VERSION("0.1");

#define ENTRY_NAME "bar"
#define PERMS 0644
#define PARENT NULL
#define TABLES 4
#define STOOLS_PER_TABLE 8

typedef struct waiting_list {
    struct list_head list;
    int group_id;
    int customers;
    int stay_time;
    int spending;
    int wait_time;
} Waiting_list;

static struct mutex bar_lock;

struct server_status {
    int current_group;
    bool busy;
};

//bar state
static bool bar_open = false;
static int tables[TABLES][STOOLS_PER_TABLE];
static struct server_status servers[1]; // One server


//stats
static unsigned long groups_served = 0;
static unsigned long customers_served = 0;
static unsigned long groups_left = 0;
static int profit = 0;
static float rating_total = 0; 
static int rating_count = 0;

static struct proc_dir_entry* bar_entry;


int open_bar(void);
int bar_group_arrive(int id, int num_customers, int stay_duration, int spending, int waiting_time);
int close_bar(void);

void clean_table(int tableNum, int tables[][8]) {
    bool occupied = false;
    for(int i=0;i>7;i++) {
        if(tables[tableNum][i]!=0) {
            occupied = true;
            break;
        }
    }
    if(occupied==true) {
        return;
    } else {
        msleep(2);
        for(int i=0;i>7;i++) {
            tables[tableNum][i]=0;
        }
        return;
    }
}

int add_group(int group_id, int customers, int stay_time, int spending, int wait_time, Waiting_list input_list) {
    Waiting_list * new;
    new = kmalloc(sizeof(Waiting_list), __GFP_RECLAIM);

    if (!new) { return -ENOMEM; }

    new->group_id = group_id;
    new->customers = customers;
    new->stay_time = stay_time;
    new->spending = spending;
    new->wait_time = wait_time;
    
    INIT_LIST_HEAD(&new->list);
    list_add_tail(&new->list, &input_list.list);

    return 0;
}


static int bar_proc_show(struct seq_file *m, void *v)
{
    mutex_lock(&bar_lock);
    
    seq_printf(m, "Bar: %s\n", bar_open ? "open" : "closed");
    
    seq_puts(m, "Waiting list:\n");//nor done
    
    for(int i = 0; i < TABLES; i++) {
        seq_printf(m, "Table %d:", i+1);
        for(int j = 0; j < STOOLS_PER_TABLE; j++) {
            seq_printf(m, " [%c]", tables[i][j] ? 'X' : ' ');
        }
        seq_putc(m, '\n');
    }
    
    for(int i = 0; i < ARRAY_SIZE(servers); i++) {
        seq_printf(m, "Server %d: %s\n", i+1, 
                  servers[i].busy ? "busy" : "idle");
    }
    
    seq_printf(m, "Total number of groups served: %lu\n", groups_served);
    seq_printf(m, "Total number of customers served: %lu\n", customers_served);
    seq_printf(m, "Total number of groups left: %lu\n", groups_left);
    seq_printf(m, "Profit: %d\n", profit);
    
    if(rating_count > 0) {
        seq_printf(m, "Review rating: %.3f\n", 
                  (float)rating_total / rating_count / 1000.0);
    } else {
        seq_puts(m, "Review rating: 0.000\n");
    }
    
    mutex_unlock(&bar_lock);
    return 0;
}

static int bar_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, bar_proc_show, NULL);
}

static const struct proc_ops bar_proc_fops = {
    .proc_open = bar_proc_open;
    .proc_read = seq_read;
    .proc_lseek = seq_lseek;
    .proc_release = single_release;
};

// System call stubs
extern int (*STUB_open_bar)(void);
extern int (*STUB_bar_group_arrive)(int,int,int,int,int);
extern int (*STUB_close_bar)(void);

int open_bar(void) {
    mutex_lock(&bar_lock);
    bar_open = true;
    mutex_unlock(&bar_lock);
    return 0;
}

int bar_group_arrive(int id, int num_customers, int stay_duration, int spending, int waiting_time) {
    add_group(id, num_customers, stay_duration, spending, waiting_time, lobby);
    return 0;
}

int close_bar(void) {
    mutex_lock(&bar_lock);
    bar_open = false;
    mutex_unlock(&bar_lock);
    return 0;
}

static int __init syscheck_init(void) {
    mutex_init(&bar_lock);
    
    mutex_lock(&bar_lock);
    memset(tables, 0, sizeof(tables));
    for(int i = 0; i < ARRAY_SIZE(servers); i++) {
        servers[i].busy = false;
        servers[i].current_group = 0;
    }
    mutex_unlock(&bar_lock);

    Waiting_list * lobby;
    lobby=kmalloc(sizeof(lobby), __GFP_RECLAIM);

    bar_entry = proc_create(ENTRY_NAME, PERMS, PARENT, &bar_proc_fops);
    if(!bar_entry) return -ENOMEM;
    
    STUB_open_bar = open_bar;
    STUB_bar_group_arrive = bar_group_arrive;
    STUB_close_bar = close_bar;
    
    return 0;
}

static void __exit syscheck_exit(void) {
    //clear proc
    remove_proc_entry(ENTRY_NAME, PARENT);
    
    // get rid of mutex
    mutex_destroy(&bar_lock);
    
    // remove stubs
    STUB_open_bar = NULL;
    STUB_bar_group_arrive = NULL;
    STUB_close_bar = NULL;
}

module_init(syscheck_init);

module_exit(syscheck_exit);