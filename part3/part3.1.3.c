//some code here
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