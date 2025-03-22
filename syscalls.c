#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>

//syscall stubs
int (*STUB_open_bar)(void) = NULL;
int (*STUB_bar_group_arrive)(void) = NULL;
int (*STUB_close_bar)(void) = NULL;
EXPORT_SYMBOL(STUB_open_bar);
EXPORT_SYMBOL(STUB_bar_group_arrive);
EXPORT_SYMBOL(STUB_close_bar);

SYSCALL_DEFINE0(open_bar){
    printk(KERN_NOTICE "Inside SYSCALL_DEFINE0 block. %s", _FUNCTION_);
    if(STUB_open_bar!=NULL) {
        return STUB_open_bar(); else return -ENOSYS;
    }
}

SYSCALL_DEFINE0(bar_group_arrive){
    printk(KERN_NOTICE "Inside SYSCALL_DEFINE0 block. %s", _FUNCTION_);
    if(STUB_bar_group_arrive!=NULL) {
        return STUB_bar_group_arrive(); else return -ENOSYS;
    }
}

SYSCALL_DEFINE0(close_bar){
    printk(KERN_NOTICE "Inside SYSCALL_DEFINE0 block. %s", _FUNCTION_);
    if(STUB_close_bar!=NULL) {
        return STUB_close_bar(); else return -ENOSYS;
    }
}