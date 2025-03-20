#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    const char *filename = "testFile";
    int file;
    remove(filename);
    file = open(filename, O_WRONLY | O_CREAT);
    write(file, "", 0);
    close(file);
    return 0;
}