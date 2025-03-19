#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "syscalls_wrap.h"

#define NUM_GROUPS 20

int generate_random_num(int min_n, int max_n) {
  return min_n + rand() % (max_n - min_n + 1);
}

int main() {
  int ret = 0;

  srand(time(NULL));

  ret = open_bar();
  if (ret != 0) {
    printf("open_bar failed, ret: %d.\n", ret);
    return 0;
  }
  printf("open_bar() done.\n");

  for (int i = 0; i < NUM_GROUPS; ++i) {
    int id = i + 1;
    int num_customers = generate_random_num(1, 8);
    int stay_duration = generate_random_num(1, 60);
    int spending = generate_random_num(1, 100);
    int waiting_time = generate_random_num(1, 20);
    printf("group id: %d, num_customers: %d, stay_duration: %d, spending: %d, waiting_time: %d\n",
            id, num_customers, stay_duration, spending, waiting_time);
    ret = bar_group_arrive(id, num_customers, stay_duration, spending, waiting_time);
    if (ret != 0) {
      printf("bar_group_arrive failed, ret: %d.\n", ret);
      break;
    }
    printf("bar_group_arrive(%d, %d, %d, %d, %d) done.\n", id, num_customers, stay_duration, spending, waiting_time);
  }

  ret = close_bar();
  if (ret != 0) {
    printf("close_bar failed, ret: %d.\n", ret);
  }
  printf("close_bar() done.\n");

  return 0;
}