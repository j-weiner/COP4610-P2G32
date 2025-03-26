#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include "bar.h"

static int abs(int x) {
    return (x < 0) ? -x : x;//local function for abs(), math unavailable in kernel
}

int bar_proc_show(struct seq_file *m, void *v) {
    Waiting_list *entry;
    mutex_lock(&bar_lock);

    seq_printf(m, "Bar: %s\n", bar_open ? "open" : "closed");
    seq_puts(m, "Waiting list: ");

    if (lobby && !list_empty(&lobby->list)) {
        list_for_each_entry(entry, &lobby->list, list) {
            seq_printf(m, "%d{%d} ", entry->group_id, entry->customers);
        }
    } else {
        seq_puts(m, "(empty)");
    }
    seq_putc(m, '\n');

    for (int i = 0; i < TABLES; i++) {
        seq_printf(m, "Table %d:", i+1);
        for (int j = 0; j < STOOLS_PER_TABLE; j++) {
            seq_printf(m, " [%c]", tables[i][j] ? 'X' : ' ');
        }
        seq_putc(m, '\n');
    }

    for (int i = 0; i < ARRAY_SIZE(servers); i++) {
        seq_printf(m, "Server %d:", i+1);
        if(servers[i].server_state==0) {
            seq_printf(m, "idle\n");
        }else if(servers[i].server_state<0) {
            seq_printf(m, "Cleaning table: %d\n", abs(servers[i].server_state));
        }else if(servers[i].server_state>0) {
            seq_printf(m, "Seating group: %d\n", servers[i].server_state);
        }
    }

    seq_printf(m, "Total groups served: %lu\n", groups_served);
    seq_printf(m, "Total customers served: %lu\n", customers_served);
    seq_printf(m, "Total groups left: %lu\n", groups_left);
    seq_printf(m, "Profit: %d\n", profit);

    if (rating_count > 0) {
        seq_printf(m, "Review rating: %d.%03d\n", rating_total / 1000, rating_total % 1000);
    } else {
        seq_puts(m, "Review rating: 0.000\n");
    }

    mutex_unlock(&bar_lock);
    return 0;
}

int bar_proc_open(struct inode *inode, struct file *file) {
    return single_open(file, bar_proc_show, NULL);
}

const struct proc_ops bar_proc_fops = {
    .proc_open = bar_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};