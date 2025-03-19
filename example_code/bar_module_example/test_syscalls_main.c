#include <stdio.h>
#include <unistd.h>
#include "test_syscalls_def.h"

int main() {
  if (open_bar() == 0)
    printf("open_bar system call exists.\n");
  else
    printf("open_bar system call does not exist.\n");

  if (bar_group_arrive(1, 2, 3, 4, 5) == 0)
    printf("bar_group_arrive system call exists.\n");
  else
    printf("bar_group_arrive system call does not exist.\n");

  if (close_bar() == 0)
    printf("close_bar system call exists.\n");
  else
    printf("close_bar system call does not exist.\n");

  return 0;
}