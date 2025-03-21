#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define Tstools 32

#define tables 4
#define stools_per_table 8

static int bar[tables][stools_per_table]={NULL};

//cell=NULL- Empty seat
//cell=0 - dirty seat
//cell>0 - group ID
//reinitialize cells to NULL after cleaning
//static bool stool_occupied[Tstools] = {false}; 

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
            bar[tableNum][i]={NULL};
        }
    }
}

bool stools_are_adjacent(int t1, int s1, int t2, int s2) {
    // input validation: check table and stool boundaries
    if (t1 < 0 || t1 >= tables || t2 < 0 || t2 >= tables ||
        s1 < 0 || s1 >= stools_per_table || s2 < 0 || s2 >= stools_per_table) {
        return false;
    }

    if (t1 == t2 && (s1 == s2 + 1 || s1 == s2 - 1)) {//adjacency within the same table
        return true;
    }

    if ((t2 == t1 + 1 && s1 == stools_per_table - 1 && s2 == 0) ||  // check next table adjacency
        (t1 == t2 + 1 && s1 == 0 && s2 == stools_per_table - 1)) {  // check previous table adjacency
        return true;
    }

    return false;
}

/*bool stools_are_adjacent(int s1, int s2) {
    // Return false if out of range, or if same stool
    if (s1 < 0 || s1 >= Tstools|| s2 < 0 || s2 >= Tstools || s1 == s2)
        return false;

    //  must be numerically +-1  apart and either in the same table or a correct linkage location
    if ((s2 == s1 + 1) || (s2 == s1 - 1)) {
        // this is to handle special linkage location
        if ((s1 == 7  && s2 == 8)  || (s1 == 8  && s2 == 7)  ||
            (s1 == 15 && s2 == 16) || (s1 == 16 && s2 == 15) ||
            (s1 == 23 && s2 == 24) || (s1 == 24 && s2 == 23)) {
            return true;
        }
        // Otherwise have to be in the  same table to be valid 
        int table1 = s1 / 8;
        int table2 = s2 / 8;
        return (table1 == table2);
    }

    return false;
}*/

int main(void) {

return 0;
}
