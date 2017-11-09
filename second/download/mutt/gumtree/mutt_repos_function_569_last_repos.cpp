static int socket_connect (int fd, struct sockaddr* sa)
{
  int sa_size;
  int save_errno;
  sigset_t set;

  if (sa->sa_family == AF_INET)
    sa_size = sizeof (struct sockaddr_in);
#ifdef HAVE_GETADDRINFO
  else if (sa->sa_family == AF_INET6)
    sa_size = sizeof (struct sockaddr_in6);
#endif
  else
  {
    dprint (1, (debugfile, "Unknown address family!\n"));
    return -1;
  }

  if (ConnectTimeout > 0)
      alarm (ConnectTimeout);

  mutt_allow_interrupt (1);

  /* FreeBSD's connect() does not respect SA_RESTART, meaning
   * a SIGWINCH will cause the connect to fail. */
  sigemptyset (&set);
  sigaddset (&set, SIGWINCH);
  sigprocmask (SIG_BLOCK, &set, NULL);

  save_errno = 0;

  if (connect (fd, sa, sa_size) < 0)
  {
      save_errno = errno;
      dprint (2, (debugfile, "Connection failed. errno: %d...\n", errno));
      SigInt = 0;	/* reset in case we caught SIGINTR while in connect() */
  }

  if (ConnectTimeout > 0)
      alarm (0);
  mutt_allow_interrupt (0);
  sigprocmask (SIG_UNBLOCK, &set, NULL);

  return save_errno;
}