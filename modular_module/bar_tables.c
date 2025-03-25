#include <linux/delay.h>
#include "bar.h"

void clean_table(int tableNum) {
    bool occupied = false;
    for (int i = 0; i < STOOLS_PER_TABLE; i++) { // Fixed loop condition
        if (tables[tableNum][i] != 0) {
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