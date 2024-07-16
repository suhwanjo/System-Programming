#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    int n, fd;
    char buf[BUFSIZE] = {0};
    char result[BUFSIZE] = {0};
    int index = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <string_to_compare>\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

    while ((n = read(fd, buf, BUFSIZE)) > 0) {
        for (int i = 0; i < n; i++) {
            if (buf[i] != ' ' && buf[i] != '\n' && buf[i] != '\t') {
                result[index++] = buf[i];
            } else {
                if (index > 0) {
                    result[index] = '\0';
                    if (strcmp(result, argv[2]) == 0) {
                        printf("Compare the : %s - Matched!\n", result);
                    } else {
                        printf("Compare the : %s\n", result);
                    }
                    index = 0;
                }
            }
        }
    }

    if (n < 0) {
        perror("read");
        exit(1);
    }

    // 마지막 단어 확인 
    if (index > 0) {
        result[index] = '\0';
        if (strcmp(result, argv[2]) == 0) {
            printf("Compare the : %s - Matched!\n", result);
        } else {
            printf("Compare the : %s\n", result);
        }
    }

    close(fd);
    return 0;
}

