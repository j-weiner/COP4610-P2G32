#include "bar_functions.h"

int add_group(int group_id, int customers, int stay_time, int spending, int wait_time, Waiting_list input_list) {
    Waiting_list * new;
    new = kmalloc(sizeof(Waiting_list), __GFP_RECLAIM);

    if (!new) { return -ENOMEM; }

    new->group_id = group_id;
    new->customers = customers;
    new->stay_time = stay_time;
    new->spending = spending;
    new->wait_time = wait_time;
    
    INIT_LIST_HEAD(&new->list)
    list_add_tail(&new->list, &input_list);

    return 0;
}
