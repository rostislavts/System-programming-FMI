#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (fork() == 0)
		write(fd, "Hello", 5);
	else
		if (fork() == 0)
			write(fd, "Hello", 5);
	close(fd);
	return 0;
}
