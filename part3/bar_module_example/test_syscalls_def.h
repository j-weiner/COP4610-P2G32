#ifndef __TEST_SYSCALLS_DEF_H__
#define __TEST_SYSCALLS_DEF_H__

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

#define __NR_OPEN_BAR 548
#define __NR_BAR_GROUP_ARRIVE 549
#define __NR_CLOSE_BAR 550

int open_bar() {
  return syscall(__NR_OPEN_BAR);
}

int bar_group_arrive(int id, int num_customers, int stay_duration, int spending, int waiting_time) {
  return syscall(__NR_BAR_GROUP_ARRIVE, id, num_customers, stay_duration, spending, waiting_time);
}

int close_bar() {
  return syscall(__NR_CLOSE_BAR);
}

#endif // __TEST_SYSCALLS_DEF_H__

