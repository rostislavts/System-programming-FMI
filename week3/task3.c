#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int n = (int)*argv[1] - 48;

	int fd = open(argv[2], O_RDONLY);
	int cnt = 0;

	const int MAX_BUFF_SIZE = 16;
	char buff[MAX_BUFF_SIZE];
	int c;

	while(c = read(fd, buff, 1)) {
		if (buff[0] == '\n')
			cnt++;

		if (cnt == n)
			break;
	}

	if (n == 0)
		lseek(fd, 0, SEEK_SET);
	
	while (c = read(fd, buff, MAX_BUFF_SIZE))
		write(1, buff, MAX_BUFF_SIZE);

	close(fd);
	
	return 0;
}

