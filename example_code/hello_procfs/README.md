## Usage

```shell
make
sudo insmod hello_proc.ko
# write to the proc file
echo "111" > /proc/hello_proc
# read from the proc file
cat /proc/hello_proc
sudo rmmod hello_proc
```