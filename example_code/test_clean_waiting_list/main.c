#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "syscalls_wrap.h"

int main() {
  int ret = 0;

  ret = open_bar();
  if (ret != 0) {
    printf("open_bar failed, ret: %d.\n", ret);
    return 0;
  }

  // Issue 4 groups of 8 customers.
  ret = bar_group_arrive(1, 8, 10, 20, 30);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }

  ret = bar_group_arrive(2, 8, 10, 20, 30);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }

  ret = bar_group_arrive(3, 8, 10, 20, 30);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }

  ret = bar_group_arrive(4, 8, 10, 20, 30);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }

  // Issue more groups with small waiting time.
  ret = bar_group_arrive(5, 1, 20, 1, 2);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }

  ret = bar_group_arrive(6, 1, 20, 1, 2);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }

  ret = bar_group_arrive(7, 1, 20, 1, 2);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }

  ret = bar_group_arrive(8, 1, 20, 1, 2);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }

  ret = bar_group_arrive(9, 1, 20, 1, 2);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }

  // Sleep to see if the bar can clean the waiting list and incrase the metrics.
  sleep(10);

close:
  ret = close_bar();
  if (ret != 0) {
    printf("close_bar failed, ret: %d.\n", ret);
  }

  return 0;
}