#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int fd1, fd2, fd3;

	fd1 = open("fff", O_CREAT | O_RDONLY, 00640);
	fd2 = open("fff", O_WRONLY);
	fd3 = open("fff", O_RDWR);
	

	write(fd2, "hello world", 11);

	const int MAX_BUFF_SIZE = 16;
	char buff[MAX_BUFF_SIZE];
	int c;

	c = read(fd3, buff, 6);
	write(1, buff, c);

	c = read(fd1, buff, 5);
	write(1, buff, c);

	write(fd3, "chil", 4);
	
	write(fd2, "!!!", 3);


	c = read(fd1, buff, 9);
	write(1, buff, c);

	close(fd1);
	close(fd2);
	close(fd3);

	return 0;
}

