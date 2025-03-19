## Usage

```shell
make
sudo insmod thread.ko
# Read the proc file will show the count incremented by threads
cat /proc/thread_example
sudo rmmod thread.ko
```