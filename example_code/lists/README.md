## Usage

```shell
make
sudo insmod random_animals.ko
# Read the proc file will triggering the add of a new animal to the list
cat /proc/animal_list
cat /proc/animal_list
cat /proc/animal_list
sudo rmmod random_animals
# Removing the module will show the stats of animals in the list
sudo dmesg
```