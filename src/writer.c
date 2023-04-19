#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    char *shm_path = argv[1];
    int fd = shm_open(shm_path,
                      O_CREAT | O_EXCL | O_RDWR,
                      S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("shm open");
        exit(1);
    }

    if (ftruncate(fd, 1024) == -1) {
        perror("ftruncate");
        exit(1);
    }

    char * shm_ptr = (char *)mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    char *str = "Hello World!!!\n";
    memcpy(shm_ptr, str, strlen(str));

    return 0;
}