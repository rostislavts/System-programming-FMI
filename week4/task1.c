#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

  int fd1, fd2;
  const int MAX_BUFF_SIZE = 512;
  char buff[MAX_BUFF_SIZE];
  int c;

  fd1 = open("f.txt", O_RDONLY);
  fd2 = dup(fd1);

  c = read(fd1, buff, 5);
  write(1, buff, c);

  c = read(fd2, buff, 5);
  write(1, buff, c);

  close(fd1);

  while(c = read(fd2, buff, MAX_BUFF_SIZE))
    write(1, buff, c);

  return 0;
}

  