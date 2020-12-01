#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

  int i;
  for (i = 0; i < 10; i++)
    write(1, "EXAMPLE\n", 8);

  return 0;
}

