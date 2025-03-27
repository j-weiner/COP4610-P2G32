# COP4610-P2G32
Project 2~
Team Members:
1. Jonathan Alcineus
2. Judah Alter
3. Joseph Weiner

Part 1: System Call Tracing
- Joseph Weiner - Judah Alter

Part 2: Timer Kernel Module
- Joseph Weiner - Jonathan Alcineus

Part 3: Bar Stools Management
Adding System Calls: Joseph Weiner, Jonathan Alcineus
Kernel Compilation: Joseph Weiner, Judah Alter
Framework Design: Joseph Weiner, Judah Alter, Jonathan Alcineus
Splitting Functions: Joseph Weiner, Jonathan Alcineus
API Designs: Joseph Weiner, Judah Alter
Waiting List: Joseph Weiner, Jonathan Alcineus, Judah Alter
Mutexes: Joseph Weiner, Jonathan Alcineus
Algorithms to pick up a group from the waiting list: Joseph Weiner
Algorithms to pick up stools for a group: Joseph Weiner


file listing:

./part1/
    -empty.c
    -empty.trace
    -part1.c
    -part1.trace
./part2/
    -timer.c
    -Makefile
./part3/
    -src
        -bar_def.h
        -bar_procfs.c
        -bar_tables.c
        -bar.c
        -bar.h
        -Makefile
    -syscall_64.tbl
    -syscalls.c
    -syscalls.h
./
- README.md

Compile part 1 with `gcc empty.c -o empty`
                    `gcc part1.c -o part1`

        part 2 with `make`
                    `sudo insmod timer.ko`
                    `cat /proc/timer`
                    `cat /proc/timer`
                    `sudo rmmod timer.ko`
        
        part 3 with `make`
                    `sudo insmod bar_module.ko`
                    //run test files
                    `sudo rmmod bar_module.ko`