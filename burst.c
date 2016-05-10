
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
  char buffer[16384];
  char new_buffer[16384];
  ssize_t bytes_read;
  ssize_t bytes_written;  
  int line_count = 0;
  int copied = 0;
  int file_count = 0;

  char *input = argv[1];
  char filename1[1000];
  char *filename2 = malloc(strlen(input) + 1);

  char *extention = strrchr(input, '.');
  strcpy(filename2, input);
  char *dot_character;
  dot_character = strrchr(filename2, '.');
  *dot_character = '\0';
  char extention2[10];

  strcpy(filename1, filename2);
  strcpy(extention2, extention);
  strcat(filename2, "1");
  strcat(filename2, extention2);
  
  char *dot_char;
  
  int out_fd;
  int out2_fd; 

  int max_lines = 10;
  
  if (argc != 2)
    {
      printf("Usage: ./burst file.txt");
      return 1;
    }
  
  int in_fd = open(argv[1], O_RDONLY);
  if (in_fd == -1)
    {
      perror ("open");
      return 2;
    }
  
  while ((bytes_read = read(in_fd, &buffer, sizeof(buffer))) > 0)
    {
      for (int i=0; i<bytes_read; i++)
	{
	  new_buffer[copied] = buffer[i];
	  copied++;
	  if (buffer[i] == '\n')
	    {
	      line_count++;
	      if (line_count == max_lines)
		{
		  file_count++;
		  char file_buffer[100];
		  strcpy(filename2, filename1);
		  sprintf(file_buffer, "%d", file_count);
		  strcat(filename2, file_buffer);
		  strcat(filename2, extention2);

		  out_fd = open(filename2, O_WRONLY | O_CREAT, 0644); 		  
		  bytes_written = write(out_fd, &new_buffer, copied);

		  if (bytes_written != copied)
		    {
		      perror("write");
		      return 3;
		    }
		  
		  copied = 0;
		  line_count = 0;
		 
		}
	    }
	}
    }
  
  if (copied > 0)
    {
      file_count++;
      char file_buffer[100];
      strcpy(filename2, filename1);
      sprintf(file_buffer, "%d", file_count);
      strcat(filename2, file_buffer);
      strcat(filename2, extention2);

      out2_fd = open(filename2, O_WRONLY | O_CREAT, 0644);
      bytes_written = write(out2_fd, &new_buffer, copied);

      if (bytes_written != copied)
	{
	  perror("write");
	  return 4;
	}
    }
  return (EXIT_SUCCESS);
}

