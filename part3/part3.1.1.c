#include <stdio.h>
#include <stdbool.h>

#define Tstools 32
/*
#define tables 4;
#define stools_per_table 8;
static int bar[tables][stools]={NULL};
//cell=NULL- Empty seat
//cell=0 - dirty seat
//cell>0 - group ID
//reinitialize cells to NULL after cleaning
*/
static bool stool_occupied[Tstools] = {false}; 


/*
static int bar_array[tables][stools];
bool stools_are_adjacent(int t1, int s1, int t2, int s2) {
    if( (t1||t2) < 0 || (t1||t2) >= tables || (s1||s2) < 0 || (s1||s2) >= stools) {
        return false; //input validation
    } else if(t1==t2 && (s1-1==s2||s1+1==s2)) {
        return true;//if s1 & s2 are at the same table, & s1 is only one off s2, they are adjacent
    } else {
        switch(t1) {
        case 0:
            if(t2!=1&&s1!=7&&s2!=0) return false;
        case 1:
            if(t2!=)
            
        }
    }
};
*/

bool stools_are_adjacent(int s1, int s2) {
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
}

int main(void) {

return 0;
}
