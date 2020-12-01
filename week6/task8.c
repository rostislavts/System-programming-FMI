#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int status;
	if (fork() == 0) {
		if (execlp(argv[1], argv[1], NULL) == -1)
			exit(-1);
	} else {
		wait(&status);
		if (status != 0)
			exit(-1);
		execlp(argv[2], argv[2], NULL);
	}
	return 0;
}
