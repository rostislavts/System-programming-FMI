#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef int bool;
#define true 1;
#define false 0;

const int UPPER_BOUND = 10E4;

int main(int argc, char* argv[]) {
    int fd = open("f", O_CREAT | O_TRUNC | O_RDWR, 0644);
    int a = 0;
    char buff[64];

    write(fd, &a, sizeof(int));

    int pid = fork();
    
    for (int i = 0; i < UPPER_BOUND; i++) {
        lseek(fd, 0, 0);
        read(fd, &a, sizeof(int));
        if (pid == 0) {
            a += 1;
            sprintf(buff, "     %d\n", a);
        } else {
            a += 2;
            sprintf(buff, "%d\n", a);
        }
        
        write(1, buff, strlen(buff));

        lseek(fd, 0, 0);
        write(fd, &a, sizeof(int));
    }
	return 0;
}