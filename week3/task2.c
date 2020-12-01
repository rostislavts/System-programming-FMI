#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int fd1, fd2;
	fd1 = open("f1", O_RDWR);
	fd2 = open("f1", O_RDWR);

	lseek(fd1, -2, SEEK_END);

	write(fd1, "wxyz", 4);

	lseek(fd2, 5, SEEK_SET);
	write(fd2, "12", 2);

	const int MAX_BUFF_SIZE = 16;
	char buff[MAX_BUFF_SIZE];
	int c;

	lseek(fd1, 0, SEEK_SET);
	while (c = read(fd1, buff, MAX_BUFF_SIZE))
		write(1, buff, c);

	close(fd1);
	close(fd2);

	return 0;
}

