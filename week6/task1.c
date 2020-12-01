#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	fork();
	fork();

	printf("PID: %d\n", getpid());
	printf("Parent PID: %d\n\n", getppid());
  
	return 0;
}
