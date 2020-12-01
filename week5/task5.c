#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int status1, status2, status3;
	int pid1, pid2, pid3;
	pid1 = fork();
	if (pid1 == 0) {
		pid2 = fork();
		if (pid2 == 0) {
			pid3 = fork();
			if (pid3 == 0) {
				execlp(argv[1], argv[1], NULL);
				exit(status3);
			} else {
				wait(&status3);
				printf("Status: %d, Pid: %d\n", status3, pid3);
				execlp(argv[2], argv[2], NULL);
				exit(status2);
			}
		} else {
			wait(&status2);
			printf("Status: %d, Pid: %d\n", status2, pid2);
			execlp(argv[3], argv[3], NULL);
			exit(status1);
		}
	} else {
		wait(&status1);
		printf("Status: %d, Pid: %d\n", status1, pid1);
	}
	return 0;
}
