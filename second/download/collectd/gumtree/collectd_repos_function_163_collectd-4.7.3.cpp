static int exec_init (void) /* {{{ */
{
  struct sigaction sa;

  memset (&sa, '\0', sizeof (sa));
  sa.sa_handler = sigchld_handler;
  sigaction (SIGCHLD, &sa, NULL);

  return (0);
}