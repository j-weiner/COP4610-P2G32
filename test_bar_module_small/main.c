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
  printf("open_bar done.\n");

  ret = bar_group_arrive(1, 5, 5, 20, 10);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }
  printf("bar_group_arrive(1, 5, 5, 20, 10) done.\n");

  ret = bar_group_arrive(2, 4, 5, 20, 10);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }
  printf("bar_group_arrive(2, 4, 5, 20, 10) done.\n");

  ret = bar_group_arrive(3, 3, 5, 6, 20);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }
  printf("bar_group_arrive(3, 3, 5, 6, 20) done.\n");

  // This group should leave before seating if the algorithm does not select
  // the Least-Waiting-Time group.
  ret = bar_group_arrive(4, 5, 3, 7, 2);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }
  printf("bar_group_arrive(4, 5, 3, 7, 2) done.\n");

  // Sleep to see if stools are marked as drity and table are under cleaning.
  printf("sleeping 10 seconds ...\n");
  sleep(10);

  ret = bar_group_arrive(5, 3, 7, 8, 9);
  if (ret != 0) {
    printf("bar_group_arrive failed, ret: %d.\n", ret);
    goto close;
  }
  printf("bar_group_arrive(5, 3, 7, 8, 9) done.\n");

  sleep(5);

close:
  ret = close_bar();
  if (ret != 0) {
    printf("close_bar failed, ret: %d.\n", ret);
  }
  printf("close_bar done.\n");

  return 0;
}