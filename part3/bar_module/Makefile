# Kernel module name
obj-m += bar.o

# Source files for the module
bar-y := bar_functions.o

# Kernel build directory (adjust if needed)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build

# Module build targets
all:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean

# File dependencies
bar_functions.o: bar_functions.h
bar.o: bar_functions.h