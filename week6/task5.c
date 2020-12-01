#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) { 
	// Given 2 file names as args
	int status;
	int fd1 = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (fork() == 0) {
		int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 00644);
		close(fd1);
		dup(fd2);
		write(fd1, "hello2", 6);
	} else {
		wait(&status);
		write(fd1, "hello1", 6);
	}
	write(1, "hello3", 6);
	write(fd1, "hello4", 6); // Redirected to the second file
	return 0;
}
