  int pid;
  int to_child_pipe[2];
  int from_child_pipe[2];

  if (pipe(to_child_pipe) < 0 ||
      pipe(from_child_pipe) < 0) {
    fprintf(stderr,"pipe: %s\n",strerror(errno));
    exit_cleanup(1);
  }


  pid = fork();
  if (pid < 0) {
    fprintf(stderr,"fork: %s\n",strerror(errno));
    exit_cleanup(1);
  }

  if (pid == 0)
    {
      if (dup2(to_child_pipe[0], STDIN_FILENO) < 0 ||
	  close(to_child_pipe[1]) < 0 ||
	  close(from_child_pipe[0]) < 0 ||
	  dup2(from_child_pipe[1], STDOUT_FILENO) < 0) {
	fprintf(stderr,"Failed to dup/close : %s\n",strerror(errno));
	exit_cleanup(1);
      }
      execvp(command[0], command);
      fprintf(stderr,"Failed to exec %s : %s\n",
	      command[0],strerror(errno));
      exit_cleanup(1);
    }

  if (close(from_child_pipe[1]) < 0 ||
      close(to_child_pipe[0]) < 0) {
    fprintf(stderr,"Failed to close : %s\n",strerror(errno));   
    exit_cleanup(1);
  }

  *f_in = from_child_pipe[0];
  *f_out = to_child_pipe[1];
  
  return pid;
}


void out_of_memory(char *str)
{
  fprintf(stderr,"out of memory in %s\n",str);
  exit_cleanup(1);
}


#ifndef HAVE_STRDUP
 char *strdup(char *s)
