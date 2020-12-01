#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

  if (argc < 2)
    return 1;
 
  int i;
  for (i = 1; i <= 10; i++)
    write(1, "EXAMPLE\n", 8);

  int fd1 = dup(1);
  close(1);
  int fd2 = open(argv[1], O_WRONLY);

  char str[10];
  for (i = 1; i <= 10; i++) {
	  sprintf(str, "i=%d\n", i);    
    write(1, str, strlen(str));
  }

  close(1);
  int fd3 = dup(fd1);

  for (i = 1; i <= 10; i++)
    write(1, "HELLO\n", 6);

  return 0;
}
