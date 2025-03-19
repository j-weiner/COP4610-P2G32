obj-m += test_syscalls_module.o

all: test_syscalls_module.ko test_syscalls_exist

run:
	./test_syscalls_exist

test_syscalls_exist: test_syscalls_exist.c syscalls_wrap.h
	gcc test_syscalls_exist.c -o test_syscalls_exist

test_syscalls_module.ko: test_syscalls_module.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY: all clean run

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm test_syscalls_exist *.o *.ko