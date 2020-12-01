#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
  char *cmd[] = { "grep", "int", argv[1], NULL };
  execvp("wrongCmd", cmd);

  return 0;
}
