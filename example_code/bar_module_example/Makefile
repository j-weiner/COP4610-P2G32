obj-m += test_syscalls_module.o

all: test_syscalls_module.ko test_syscalls_main

run:
	./test_syscalls_main

test_syscalls_main: test_syscalls_main.c test_syscalls_def.h
	gcc test_syscalls_main.c -o test_syscalls_main

test_syscalls_module.ko: test_syscalls_module.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY: all clean run

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm test_syscalls_main *.o *.ko