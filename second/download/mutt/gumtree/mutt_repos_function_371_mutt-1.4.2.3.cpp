int raw_socket_open (CONNECTION* conn)
{
  int rc;
  int fd;

#ifdef HAVE_GETADDRINFO
/* --- IPv4/6 --- */

  /* "65536\0" */
  char port[6];
  struct addrinfo hints;
  struct addrinfo* res;
  struct addrinfo* cur;

  /* we accept v4 or v6 STREAM sockets */
  memset (&hints, 0, sizeof (hints));

  if (option (OPTUSEIPV6))
    hints.ai_family = AF_UNSPEC;
  else
    hints.ai_family = AF_INET;

  hints.ai_socktype = SOCK_STREAM;

  snprintf (port, sizeof (port), "%d", conn->account.port);
  
  mutt_message (_("Looking up %s..."), conn->account.host);

  rc = getaddrinfo (conn->account.host, port, &hints, &res);
  if (rc)
  {
    mutt_error (_("Could not find the host \"%s\""), conn->account.host);
    return -1;
  }

  mutt_message (_("Connecting to %s..."), conn->account.host); 

  rc = -1;
  for (cur = res; cur != NULL; cur = cur->ai_next)
  {
    fd = socket (cur->ai_family, cur->ai_socktype, cur->ai_protocol);
    if (fd >= 0)
    {
      if ((rc = socket_connect (fd, cur->ai_addr)) == 0)
      {
	fcntl (fd, F_SETFD, FD_CLOEXEC);
	conn->fd = fd;
	break;
      }
      else
	close (fd);
    }
  }

  freeaddrinfo (res);

#else
  /* --- IPv4 only --- */

  struct sockaddr_in sin;
  struct hostent* he;
  int i;

  memset (&sin, 0, sizeof (sin));
  sin.sin_port = htons (conn->account.port);
  sin.sin_family = AF_INET;

  mutt_message (_("Looking up %s..."), conn->account.host);

  if ((he = gethostbyname (conn->account.host)) == NULL)
  {
    mutt_error (_("Could not find the host \"%s\""), conn->account.host);
	
    return -1;
  }

  mutt_message (_("Connecting to %s..."), conn->account.host); 

  rc = -1;
  for (i = 0; he->h_addr_list[i] != NULL; i++)
  {
    memcpy (&sin.sin_addr, he->h_addr_list[i], he->h_length);
    fd = socket (PF_INET, SOCK_STREAM, IPPROTO_IP);

    if (fd >= 0)
    {
      if ((rc = socket_connect (fd, (struct sockaddr*) &sin)) == 0)
      {
	conn->fd = fd;
	break;
      }
      else
	close (fd);
    }
  }

#endif
  if (rc)
  {
    mutt_error (_("Could not connect to %s (%s)."), conn->account.host,
	    (rc > 0) ? strerror (rc) : _("unknown error"));
    mutt_sleep (2);
    return -1;
  }
  
  return 0;
}