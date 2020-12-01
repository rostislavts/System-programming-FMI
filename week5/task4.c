#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int status;
	int pid = fork();
	if (pid == 0) {
		execvp(argv[1], argv + 1);
		exit(status);
	} else {
		wait(&status);
		printf("%d\n", status);;
	}
	return 0;
}
