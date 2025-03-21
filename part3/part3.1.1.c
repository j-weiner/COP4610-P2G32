#include <stdio.h>
#include <stdbool.h>


#define Tstools 32
static bool stool_occupied[Tstools] = {false}; 

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
