#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#define BUFSIZE 524288
int main(int argc, char *argv[])
{
	if(argc < 4){
		printf("not enough arg");
		exit(1);
	}

	int fd, fd2, n;
	char buf[BUFSIZE];
	struct timeval start, end;

	gettimeofday(&start, NULL);

	if((fd = open(argv[1], O_RDONLY)) == -1){
		perror("open");
		exit(1);
	}
	if((fd2 = open(argv[2], O_CREAT | O_EXCL | O_WRONLY, 0644)) == -1){
		perror("open");
		exit(1);
	}
	int length = atoi(argv[3]);
	while((n = read(fd, buf,length)) > 0){
		if(write(fd2, buf, n) != n){
			perror("write");
			exit(1);
		}
	}
	if(n < 0){
		perror("read");
		exit(1);
	}
	close(fd);
	close(fd2);

	gettimeofday(&end, NULL);

	long seconds = end.tv_sec - start.tv_sec;
	long microseconds = end.tv_usec - start.tv_usec;
	double elapsed = seconds + microseconds*1e-6;

	printf("It takes %.6f seconds.\n", elapsed);

	return 0;
}




