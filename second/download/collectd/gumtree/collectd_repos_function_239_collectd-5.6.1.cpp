static int create_pipe (int fd_pipe[2]) /* {{{ */
{
  char errbuf[1024];
  int status;

  status = pipe (fd_pipe);
  if (status != 0)
  {
    ERROR ("exec plugin: pipe failed: %s",
        sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }

  return 0;
}