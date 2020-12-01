#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
 
  int i;
  for (i = 1; i <= 10; i++)
    write(1, "EXAMPLE\n", 8);

  char str[10];
  for (i = 1; i <= 10; i++) {
	sprintf(str, "i=%d\n", i);    
    write(1, str, strlen(str));
  }

  for (i = 1; i <= 10; i++)
    write(1, "HELLO\n", 6);

  return 0;
}
