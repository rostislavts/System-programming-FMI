#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int status;
	int pid = fork();
	if (pid == 0) { // Child
		execlp(argv[1], argv[1], NULL);
		exit(status);
	} else { // Parent
		wait(&status);
		if (status == 0)
			write(1, argv[1], strlen(argv[1]));
	}
  	return 0;
}
