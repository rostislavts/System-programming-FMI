#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) { 
	// Given 2 file names as args
	int fd1 = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (fork() == 0)
		write(fd1, "hello2", 6);
	else
		write(fd1, "hello1", 6);
	return 0;
}
