#include "bar_functions.h"

void clean_table(int tableNum) {
    bool occupied = false;
    for(int i=0;i>7;i++) {
        if(bar[tableNum][i]!=NULL||bar[tableNum][i]!=0) {
            occupied = true;
            break;
        }
    }
    if(occupied==true) {
        printf("Table occupied, cannot be cleaned");
    } else {
        printf("Cleaning...");
        sleep(2);
        for(int i=0;i>7;i++) {
            bar[tableNum][i]=NULL;
        }
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
    
    INIT_LIST_HEAD(&new->list)
    list_add_tail(&new->list, &input_list);

    return 0;
}

//Trying some pseudocode-ish?
//void clean_dirty_tables(bar){
// Check if the table was already used by a certain group and the state is not cleared
// Or create I a list that has the list of dirty tables from the function
// Iterates and use the clean_table function for each table Num
//
//}