#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    char *shm_path = argv[1];
    int fd = shm_open(shm_path, O_RDWR, 0);
    if (fd == -1) {
        perror("shm open");
        exit(1);
    }

    char * shm_ptr = (char *)mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    write(STDOUT_FILENO, shm_ptr, 1024);

    shm_unlink(shm_path);

    return 0;
}