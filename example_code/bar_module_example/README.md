## How to Use

Run `make` to generate an the kernel module `test_syscalls_module.ko` and the executable `test_syscalls_main`.

Run the following commands:
```shell
sudo insmod test_syscalls_module.ko
make run
```
You should get a result that tells you if you have the system calls correctly installed in your new kernel. If they are not installed, you will have to check the files that were added/modified for the new system calls and recompile your kernel.

After checking, you can remove the kernel module that was used only for testing:
```shell
sudo rmmod test_syscalls_module.ko
```
