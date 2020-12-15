#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// who | wc -l
int main(int argc, char* argv[]) {
    int fd[2];
    pipe(fd);    

    if (!fork()) { // Child process
        // Redirect stdout
        close(1);
        dup(fd[1]); // fd[1] is for write
        close(fd[0]);
        close(fd[1]);

        if (execlp("who", "who", NULL) == -1) {
            exit(1);
        }
    } else { // Parent process
        // Redirect stdin
        close(0);
        dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
        
        if(execlp("wc", "wc", "-l", NULL) == -1) {
            exit(1);
        }
    }
	return 0;
}