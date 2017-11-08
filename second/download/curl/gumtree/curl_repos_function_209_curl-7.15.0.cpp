static void checkfds(void)
{
#ifdef HAVE_PIPE
  int fd[2] = { STDIN_FILENO, STDIN_FILENO };
  while( fd[0] == STDIN_FILENO ||
         fd[0] == STDOUT_FILENO ||
         fd[0] == STDERR_FILENO ||
         fd[1] == STDIN_FILENO ||
         fd[1] == STDOUT_FILENO ||
         fd[1] == STDERR_FILENO )
    pipe(fd);

  close(fd[0]);
  close(fd[1]);
#endif
}