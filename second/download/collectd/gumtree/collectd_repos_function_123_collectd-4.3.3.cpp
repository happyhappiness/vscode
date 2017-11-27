static int fork_child (program_list_t *pl, int *fd_in, int *fd_out) /* {{{ */
{
  int fd_pipe_in[2];
  int fd_pipe_out[2];
  int status;
  int pid;

  if (pl->pid != 0)
    return (-1);

  status = pipe (fd_pipe_in);
  if (status != 0)
  {
    char errbuf[1024];
    ERROR ("exec plugin: pipe failed: %s",
	sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }

  status = pipe (fd_pipe_out);
  if (status != 0)
  {
    char errbuf[1024];
    ERROR ("exec plugin: pipe failed: %s",
	sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }

  pid = fork ();
  if (pid < 0)
  {
    char errbuf[1024];
    ERROR ("exec plugin: fork failed: %s",
	sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }
  else if (pid == 0)
  {
    int fd_num;
    int fd;

    /* Close all file descriptors but the pipe end we need. */
    fd_num = getdtablesize ();
    for (fd = 0; fd < fd_num; fd++)
    {
      if ((fd == fd_pipe_in[0]) || (fd == fd_pipe_out[1]))
	continue;
      close (fd);
    }

    /* If the `out' pipe has the filedescriptor STDIN we have to be careful
     * with the `dup's below. So, if this is the case we have to handle the
     * `out' pipe first. */
    if (fd_pipe_out[1] == STDIN_FILENO)
    {
      int new_fileno = (fd_pipe_in[0] == STDOUT_FILENO)
	? STDERR_FILENO : STDOUT_FILENO;
      dup2 (fd_pipe_out[1], new_fileno);
      close (fd_pipe_out[1]);
      fd_pipe_out[1] = new_fileno;
    }
    /* Now `fd_pipe_out[1]' is either `STDOUT' or `STDERR', but definitely not
     * `STDIN_FILENO'. */

    /* Connect the `in' pipe to STDIN */
    if (fd_pipe_in[0] != STDIN_FILENO)
    {
      dup2 (fd_pipe_in[0], STDIN_FILENO);
      close (fd_pipe_in[0]);
      fd_pipe_in[0] = STDIN_FILENO;
    }

    /* Now connect the `out' pipe to STDOUT and STDERR */
    if (fd_pipe_out[1] != STDOUT_FILENO)
      dup2 (fd_pipe_out[1], STDOUT_FILENO);
    if (fd_pipe_out[1] != STDERR_FILENO)
      dup2 (fd_pipe_out[1], STDERR_FILENO);

    /* If the pipe has some FD that's something completely different, close it
     * now. */
    if ((fd_pipe_out[1] != STDOUT_FILENO) && (fd_pipe_out[1] != STDERR_FILENO))
    {
      close (fd_pipe_out[1]);
      fd_pipe_out[1] = STDOUT_FILENO;
    }

    exec_child (pl);
    /* does not return */
  }

  close (fd_pipe_in[0]);
  close (fd_pipe_out[1]);

  if (fd_in != NULL)
    *fd_in = fd_pipe_in[1];
  else
    close (fd_pipe_in[1]);

  if (fd_out != NULL)
    *fd_out = fd_pipe_out[0];
  else
    close (fd_pipe_out[0]);

  return (pid);
}