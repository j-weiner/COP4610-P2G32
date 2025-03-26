#include <linux/delay.h>
#include "bar.h"

void clean_table(int tableNum) {
    bool occupied = false;
    for (int i = 0; i < STOOLS_PER_TABLE; i++) { // Fixed loop condition
        if (tables[tableNum][i] !<= 0) {
            occupied = true;
            break;
        }
    }
    if (!occupied) {
        msleep(2);
        for (int i = 0; i < STOOLS_PER_TABLE; i++) {
            tables[tableNum][i] = 0;
        }
    }
}

int find_available_table(int needed_stools) {

};

void occupy_table(int table_idx, int group_id, int customers) {
    for (int i = 0; i < customers; i++) {
        int stool_idx = table_idx + i;
        tables[stool_idx / STOOLS_PER_TABLE][stool_idx % STOOLS_PER_TABLE] = group_id;
    }
}