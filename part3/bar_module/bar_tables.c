#include <linux/delay.h>
#include "bar.h"

static bool are_stools_available(int start_idx, int needed_stools) {
    for (int i = 0; i < needed_stools; i++) {//checks if a given 'range' of stools is available
        if (tables[start_idx / STOOLS_PER_TABLE][start_idx % STOOLS_PER_TABLE] != 0) {
            return false;
        }
    }
    return true;
}

void clean_table(int tableNum) {
    bool occupied = false;
    for (int i = 0; i < STOOLS_PER_TABLE; i++) {
        if (tables[tableNum][i] > 0) {
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
    if (needed_stools < 1 || needed_stools > STOOLS_PER_TABLE) {// if group size is invalid
        return -1;
    }
    for (int i = 0; i <= 32 - needed_stools; i++) {
        if ((i + needed_stools - 1) >= 32 && (i / STOOLS_PER_TABLE) == (TABLES - 1)) {
            continue; //if starting index will wrap from 32->0, skip
        }
        if (are_stools_available(i, needed_stools)) {
            return i; // return current stool index
        }
    }

    return -1; // No available stools found
};

void occupy_table(int table_idx, int group_id, int customers) {
    for (int i = 0; i < customers; i++) {
        int stool_idx = table_idx + i;
        tables[stool_idx / STOOLS_PER_TABLE][stool_idx % STOOLS_PER_TABLE] = group_id;
    }
    msleep(2);
}