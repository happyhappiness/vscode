static int fork_child (program_list_t *pl)
{
  int fd_pipe[2];
  int status;

  if (pl->pid != 0)
    return (-1);

  status = pipe (fd_pipe);
  if (status != 0)
  {
    char errbuf[1024];
    ERROR ("exec plugin: pipe failed: %s",
	sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }

  pl->pid = fork ();
  if (pl->pid < 0)
  {
    char errbuf[1024];
    ERROR ("exec plugin: fork failed: %s",
	sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }
  else if (pl->pid == 0)
  {
    close (fd_pipe[0]);

    /* Connect the pipe to STDOUT and STDERR */
    if (fd_pipe[1] != STDOUT_FILENO)
      dup2 (fd_pipe[1], STDOUT_FILENO);
    if (fd_pipe[1] != STDERR_FILENO)
      dup2 (fd_pipe[1], STDERR_FILENO);
    if ((fd_pipe[1] != STDOUT_FILENO) && (fd_pipe[1] != STDERR_FILENO))
      close (fd_pipe[1]);

    exec_child (pl);
    /* does not return */
  }

  close (fd_pipe[1]);
  return (fd_pipe[0]);
}