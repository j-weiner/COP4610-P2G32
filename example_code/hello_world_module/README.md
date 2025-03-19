```shell
make
sudo insmod hello.ko
# This command display the kernel logs
# You can also use `sudo dmesg | less` to read it by the cmd `less`
sudo dmesg
sudo rmmod hello.ko
```