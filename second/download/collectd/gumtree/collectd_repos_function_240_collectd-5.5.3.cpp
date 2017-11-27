static void close_pipe (int fd_pipe[2]) /* {{{ */
{
  if (fd_pipe[0] != -1)
    close (fd_pipe[0]);

  if (fd_pipe[1] != -1)
    close (fd_pipe[1]);
}