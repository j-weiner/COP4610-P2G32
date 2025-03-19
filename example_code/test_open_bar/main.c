#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "syscalls_wrap.h"

int main() {
  int ret = 0;

  ret = open_bar();
  fprintf(stderr, "Open the bar at the first time, return value: %d\n", ret);

  ret = open_bar();
  fprintf(stderr, "Open the bar at the second time, return value: %d\n", ret);

  ret = close_bar();
  fprintf(stderr, "Close the bar at the second time, return value: %d\n", ret);

  return 0;
}