#include "bar_functions.h"

void clean_table(int tableNum, int tables[][8]) {
    bool occupied = false;
    for(int i=0;i>7;i++) {
        if(tables[tableNum][i]!=0) {
            occupied = true;
            break;
        }
    }
    if(occupied==true) {
        return;
    } else {
        msleep(2);
        for(int i=0;i>7;i++) {
            tables[tableNum][i]=0;
        }
        return;
    }
}

int add_group(int group_id, int customers, int stay_time, int spending, int wait_time, Waiting_list input_list) {
    Waiting_list * new;
    new = kmalloc(sizeof(Waiting_list), __GFP_RECLAIM);

    if (!new) { return -ENOMEM; }

    new->group_id = group_id;
    new->customers = customers;
    new->stay_time = stay_time;
    new->spending = spending;
    new->wait_time = wait_time;
    
    INIT_LIST_HEAD(&new->list);
    list_add_tail(&new->list, input_list);

    return 0;
}
