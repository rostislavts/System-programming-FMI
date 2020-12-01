#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 00644);
	int status;
	if (fork() == 0) {
		write(fd, "Hello", 5);
		exit(status);
	} else {
		wait(&status);
		lseek(fd, 0, 0);
		char buff[2];
		int c;
		while (c = read(fd, buff, 2)) {
			write(1, buff, 2);
			write(1, " ", 1);
		}
	}
	close(fd);
	return 0;
}
