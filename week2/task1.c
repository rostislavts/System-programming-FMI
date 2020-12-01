#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

	int fd = open("./aa", O_RDONLY);
	int c;
	const int MAX_SIZE = 512;
	char buff[MAX_SIZE];

	int i;
	for (i = 5; i >= 1; i--) {
		c = read(fd, buff, i);

		//buff[c] = '\0';
		printf("%s\n", buff);

	}

	return 0;
}