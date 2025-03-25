obj-m += bar_module.o
bar_module-objs := bar.o bar_procfs.o bar_tables.o

all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean