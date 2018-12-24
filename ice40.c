#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



/* Reads characters from the pipe and echoes them to stdout. */
void
read_from_pipe (int file)
{
  FILE *stream;
  int c;
  stream = fdopen (file, "r");
  while ((c = fgetc (stream)) != EOF)
  //while((c = fdopen(file, "r")) != EOF)
    putchar (c);
  fclose (stream);
}

/* Writes hello to the pipe. */
void write_to_pipe (int file)
{
  printf ("Hello\n");
 
}


int main(void) {
  
 pid_t pid;
  int mypipe[2];

  /* Creating the pipe. */
  if (pipe (mypipe))
    {
      fprintf (stderr, "Pipe failed.\n");
      return EXIT_FAILURE;
    }
  
    /* Creating the child process. */
  pid = fork ();
  if (pid == (pid_t) 0)
    {
      /* This is the child process.
         Close other end first. */
      close (mypipe[1]);
      read_from_pipe (mypipe[0]);
      return EXIT_SUCCESS;
    }
  else if (pid < (pid_t) 0)
    {
      /* The fork failed. */
      fprintf (stderr, "Fork failed.\n");
      return EXIT_FAILURE;
    }
  else
    {
      // This is the parent process.
      int x;
      for(x = 0; x < 10; x++) {
	write_to_pipe (mypipe[1]);
        close (mypipe[0]); //close the other end
      }
	
	return EXIT_SUCCESS;
      }
}