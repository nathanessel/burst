/*
--------------------------
Name:	Nathan Essel
Email:	nve1@zips.uakron.edu
Program:	burst.c
Description:	Split a file into separate files based on the number of lines specified by the user.
--------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  char buffer[16384];
  int bytes_read;
  int line_count = 0;

  int fd = open(argv[1], O_RDONLY);

  while (bytes_read = read(fd, buffer, sizeof(buffer)))
  {
    int i;
    for (i=0; i<bytes_read; i++)
      if (buffer[i] == '\n')
	++line_count;
  }

  printf("Number of lines %d\n",line_count);
  
}
