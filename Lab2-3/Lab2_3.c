#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    int n, fd;
    unsigned char byte; // unsigned char로 음수 값 방지

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

    while ((n = read(fd, &byte, 1)) > 0) {
        if (byte >= 32 && byte <= 126) { // ASCII 문자 범위
            printf("%c", byte);
        } else {
            off_t offset = byte % 32;
            if (lseek(fd, offset, SEEK_CUR) == -1) {
                perror("lseek");
                close(fd);
                exit(1);
            }
        }
    }
    printf("\n");
    

    if (n < 0) {
        perror("read");
        exit(1);
    }

    close(fd);
    return 0;
}

