#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if (argc < 2)
  	return 1;

  int fd1 = open(argv[1], O_CREAT | O_WRONLY, 00644);

  close(1);
  int fd2 = dup(fd1);

  int i;
  for (i = 0; i < 10; i++)
    write(1, "EXAMPLE\n", 8);

  return 0;
}
