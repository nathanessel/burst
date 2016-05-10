
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  char buffer[16384];
  char new_buffer[16384];
  ssize_t bytes_read;
  ssize_t bytes_written;  
  int line_count = 0;
  int copied = 0;
  
  int in_fd = open(argv[1], O_RDONLY);
  int out_fd = open("out1.txt", O_WRONLY | O_CREAT, 0644);
  int out2_fd = open("out2.txt", O_WRONLY | O_CREAT, 0644); 
  
  while ((bytes_read = read(in_fd, &buffer, sizeof(buffer))) > 0)
    {
      for (int i=0; i<bytes_read; i++)
	{
	  new_buffer[copied] = buffer[i];
	  copied++;
	  if (buffer[i] == '\n')
	    {
	      line_count++;
	      if (line_count == 2)
		{
		  bytes_written = write(out_fd, &new_buffer, copied);
		  copied = 0;
		}
	    }
	}
    }
  
  if (copied > 0)
    {
      bytes_written = write(out2_fd, &new_buffer, copied);
    }
  
  return 1;
  printf("Number of lines %d\n",line_count);
}

