#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include "bar.h"

int bar_proc_show(struct seq_file *m, void *v) {
    mutex_lock(&bar_lock);
    
    seq_printf(m, "Bar: %s\n", bar_open ? "open" : "closed");
    seq_puts(m, "Waiting list:\n");
    
    for (int i = 0; i < TABLES; i++) {
        seq_printf(m, "Table %d:", i+1);
        for (int j = 0; j < STOOLS_PER_TABLE; j++) {
            seq_printf(m, " [%c]", tables[i][j] ? 'X' : ' ');
        }
        seq_putc(m, '\n');
    }
    
    for (int i = 0; i < ARRAY_SIZE(servers); i++) {
        seq_printf(m, "Server %d: %s\n", i+1, servers[i].busy ? "busy" : "idle");
    }
    
    seq_printf(m, "Total groups served: %lu\n", groups_served);
    seq_printf(m, "Total customers served: %lu\n", customers_served);
    seq_printf(m, "Total groups left: %lu\n", groups_left);
    seq_printf(m, "Profit: %d\n", profit);
    seq_printf(m, "Review rating: %.3f\n", (rating_count > 0) ? (rating_total / rating_count / 1000.0) : 0.0);
    
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