#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/timekeeping.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joseph Weiner, Jonathan Alcineus, Judah Alter");
MODULE_DESCRIPTION("Timer Kernel Module");
//Started from example code provided by cop4610t
#define ENTRY_NAME "timer"
#define PERMS 0644
#define PARENT NULL

static struct proc_dir_entry* timer_entry;
static struct timespec64 last_time;
static bool first = true;

static ssize_t timer_read(struct file *file, char __user *ubuf, size_t count, loff_t *ppos)
{
    struct timespec64 ts_now;
    char buf[256];
    int len = 0;

    if (*ppos > 0)
    // Do not process this read if request from the offset > 0
        return 0;

    ktime_get_real_ts64(&ts_now);
    
    if (first) {
        len = snprintf(buf, sizeof(buf), "current time: %lld.%09ld\n", (long long)ts_now.tv_sec, ts_now.tv_nsec);
        first = false;
        last_time = ts_now;
    } else {
        struct timespec64 elapsed = {
            .tv_sec = ts_now.tv_sec - last_time.tv_sec,
            .tv_nsec = ts_now.tv_nsec - last_time.tv_nsec
        };
    
        if (elapsed.tv_nsec < 0) {
            elapsed.tv_sec--;
            elapsed.tv_nsec += NSEC_PER_SEC;
        }
    
        len = snprintf(buf, sizeof(buf), "current time: %lld.%09ld\nelapsed time: %lld.%09ld\n",//string to be printed
        (long long)ts_now.tv_sec, ts_now.tv_nsec, (long long)elapsed.tv_sec, elapsed.tv_nsec);//variables

        last_time = ts_now;
    }
    return simple_read_from_buffer(ubuf, count, ppos, buf, len);
    // Alternative: use copy_from_user then set *ppos = the bytes copied to the user.
}

static const struct proc_ops timer_fops = {
    .proc_read = timer_read,
};

static int __init timer_init(void)
{
    timer_entry = proc_create(ENTRY_NAME, PERMS, PARENT, &timer_fops);
    if (!timer_entry) {
        return -ENOMEM;
    }
    return 0;
}

static void __exit timer_exit(void)
{
    proc_remove(timer_entry);
}

module_init(timer_init);
module_exit(timer_exit);