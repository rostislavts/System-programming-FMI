#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int fd1, fd2, fd3;

	fd1 = open("fff1", O_CREAT | O_RDONLY, 00640);
	fd2 = open("fff1", O_WRONLY);
	fd3 = open("fff1", O_RDWR);
	
	write(fd3, "hello", 5);
	write(fd2, "worlds", 6);

	const int MAX_BUFF_SIZE = 16;
	char buff[MAX_BUFF_SIZE];
	int c;

	c = read(fd1, buff, 6);
	write(1, buff, c);

	close(fd2);

	write(fd3, "oops", 4);

	c = read(fd1, buff, 6);
	write(1, buff, c);

	return 0;
}

