obj-m += bar_module.o
bar_module-objs := bar.o bar_procfs.o bar_tables.o

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean