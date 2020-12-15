#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// cmd1 | cmd2  Given in argv without parameters 
int main(int argc, char* argv[]) {
    if (argc != 3) {
        exit(1);
    }

    int fd[2];
    pipe(fd);

    if (!fork()) { // Child process
        // Redirect stdout
        close(1);
        dup(fd[1]); // fd[1] is for write
        close(fd[0]);
        close(fd[1]);

        if (execlp(argv[1], argv[1], NULL) == -1) {
            exit(1);
        }
    } else { // Parent process
        // Redirect stdin
        close(0);
        dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
        
        if(execlp(argv[2], argv[2], NULL) == -1) {
            exit(1);
        }
    }
	return 0;
}