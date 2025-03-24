#ifndef BAR_FUNCTIONS_H
#define BAR_FUNCTIONS_H

typedef struct waiting_list {
    struct list_head list;
    int group_id;
    int customers;
    int stay_time;
    int spending;
    int wait_time;
} Waiting_list;

int add_group(int, int, int, int, int);

#endif