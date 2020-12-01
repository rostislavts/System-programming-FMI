#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int fd = open("task8.txt", O_RDWR);

	char c;

	for (int i = 0; i < 25; i++) {
		c = 'a' + rand(); 
		write(fd, &c, 1);
	}

	int k;
	const int MAX_SIZE = 64;
	char buff[MAX_SIZE];

	lseek(fd, 0, 0);

	while (k = read(fd, buff, 10))
		printf("%d\n", k);;


	return 0;
}