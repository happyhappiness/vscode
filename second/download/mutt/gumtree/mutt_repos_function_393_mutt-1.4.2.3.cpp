static int tunnel_socket_open (CONNECTION *conn)
{
  TUNNEL_DATA* tunnel;
  int pid;
  int rc;
  int pin[2], pout[2];

  tunnel = (TUNNEL_DATA*) safe_malloc (sizeof (TUNNEL_DATA));
  conn->sockdata = tunnel;

  mutt_message (_("Connecting with \"%s\"..."), Tunnel);

  if ((rc = pipe (pin)) == -1)
  {
    mutt_perror ("pipe");
    return -1;
  }
  if ((rc = pipe (pout)) == -1)
  {
    mutt_perror ("pipe");
    return -1;
  }

  mutt_block_signals_system ();
  if ((pid = fork ()) == 0)
  {
    mutt_unblock_signals_system (0);
    if (dup2 (pout[0], STDIN_FILENO) < 0 || dup2 (pin[1], STDOUT_FILENO) < 0)
      _exit (127);
    close (pin[0]);
    close (pin[1]);
    close (pout[0]);
    close (pout[1]);
    close (STDERR_FILENO);

    /* Don't let the subprocess think it can use the controlling tty */
    setsid ();

    execl (EXECSHELL, "sh", "-c", Tunnel, NULL);
    _exit (127);
  }
  mutt_unblock_signals_system (1);

  if (pid == -1)
  {
    close (pin[0]);
    close (pin[1]);
    close (pout[0]);
    close (pout[1]);
    mutt_perror ("fork");
    return -1;
  }
  if (close (pin[1]) < 0 || close (pout[0]) < 0)
    mutt_perror ("close");

  fcntl (pin[0], F_SETFD, FD_CLOEXEC);
  fcntl (pout[1], F_SETFD, FD_CLOEXEC);

  tunnel->readfd = pin[0];
  tunnel->writefd = pout[1];
  tunnel->pid = pid;

  conn->fd = 42; /* stupid hack */

  return 0;
}