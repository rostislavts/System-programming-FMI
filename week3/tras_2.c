#include <stdio.h>
#include <fcntl.h>
main( int argc, char *argv[])
{
   int fdi, fdo,k,broi,i=0,status;
   char buff[40],c;
   if (( fdi = open ( "ffff", O_RDWR)) == -1)
    {  printf("\n Cannot open \n"); exit(1);}
         read(fdi,buff,7);
         write(1, buff,7);
        write(1,"hap",3);
        write(fdi,"teacher",7);
        write(1,"py child",8);
}


/*
	Input file

I am a student!'\n'	

*/