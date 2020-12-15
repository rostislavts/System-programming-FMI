#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// who | grep s81xxx | wc -l
int main(int argc, char* argv[]) {
    
    int fd1[2];
    int fd2[2];

    pipe(fd1);
    pipe(fd2);

    if (!fork()) { // Child process

        if (!fork()) { // Grandchild process
            // Redirect stdout of the who command 
            close(1);
            dup(fd1[1]);
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);
            close(fd2[1]);

            if (execlp("who", "who", NULL) == -1) {
                exit(1);
            }
        } else { // Child process
            // Redirect stdin of the grep command
            close(0);
            dup(fd1[0]);
            close(fd1[0]);
            close(fd1[1]);

            // Redirect stdout of the grep command through another pipe
            close(1);
            dup(fd2[1]);
            close(fd2[0]);
            close(fd2[1]);

            if (execlp("grep", "grep", "rostislavts", NULL) == -1) {
                exit(1);
            }
        }
    } else { // Parent process
        // Redirect stdin
        close(0);
        dup(fd2[0]);
        close(fd2[0]);
        close(fd2[1]);
        close(fd1[0]);
        close(fd1[1]);
        
        if(execlp("wc", "wc", "-l", NULL) == -1) {
            exit(1);
        }
    }
	return 0;
}