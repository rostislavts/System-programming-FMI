#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	// Given 2 commands as arguments
	int status;
	int pid1, pid2;
	int resultPid;
	pid1 = fork();
	if (pid1 == 0) {
		printf("%d\n", getpid());
		execlp(argv[1], argv[1], NULL);
	} else if (pid2 == 0) {
		printf("%d\n", getpid());
		execlp(argv[2], argv[2], NULL);
	} else {
		pid2 = fork();
		wait(&status);
		exit(0);	
	}
	return 0;
}
