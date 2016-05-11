
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char* argv[])
{
  
  static struct option long_options[] = {
    {"version", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {"maxlines", required_argument, 0, 'm'},
    {0,0,0,0}
  };

  int max_lines = 10;
  int c = 0;
  int option_index = 0;
  while ((c = getopt_long(argc, argv, "h:v:m:",
			  long_options, &option_index)) != -1) {
    switch (c) {
    case 'h' :
      printf("burst 1.0, a file splitter.\nUsage: burst [OPTION] filename\n\nMandatory arguments to long options are mandatory for short options too.\n\n-v, --version         Displays the version of burst and exits.\n-h, --help            Prints this help.\n-m, --maxlines=int    The maximum number of lines in each file.\n");
      return 1;
      break;
    case 'v' :
      printf("busrt Version 1.0\n2016 Nathan Essel\n\nburst comes with NO WARRANTY, to the extent permitted by law.\nThis is free software: you are free to change and redistribute it.\n");
      return 1;
      break;
    case 'm' :
      max_lines = atoi(optarg);
      
    }
  }

  if (argc < 2)
    {
      printf("Usage: burst [OPTION] filename\n");
      return 1;
    }

  int in_fd = open(argv[argc-1], O_RDONLY);
  if (in_fd == -1)
    {
      perror ("open");
      return 2;
    }
  
  char buffer[16384];
  char new_buffer[16384];
  ssize_t bytes_read;
  ssize_t bytes_written;  
  int line_count = 0;
  int copied = 0;
  int file_count = 0;

  char *input = argv[argc-1];
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

