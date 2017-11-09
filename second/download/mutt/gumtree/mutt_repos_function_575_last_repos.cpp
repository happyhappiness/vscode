int raw_socket_open (CONNECTION* conn)
{
  int rc;
  int fd;

  char *host_idna = NULL;
  
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
  
# ifdef HAVE_LIBIDN
  if (idna_to_ascii_lz (conn->account.host, &host_idna, 1) != IDNA_SUCCESS)
  {
    mutt_error (_("Bad IDN \"%s\"."), conn->account.host);
    return -1;
  }
# else
  host_idna = conn->account.host;
# endif

  if (!option(OPTNOCURSES))
    mutt_message (_("Looking up %s..."), conn->account.host);
  
  rc = getaddrinfo (host_idna, port, &hints, &res);

# ifdef HAVE_LIBIDN
  FREE (&host_idna);
# endif

  if (rc)
  {
    mutt_error (_("Could not find the host \"%s\""), conn->account.host);
    mutt_sleep (2);
    return -1;
  }

  if (!option(OPTNOCURSES))
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

# ifdef HAVE_LIBIDN
  if (idna_to_ascii_lz (conn->account.host, &host_idna, 1) != IDNA_SUCCESS)
  {
    mutt_error (_("Bad IDN \"%s\"."), conn->account.host);
    return -1;
  }
# else
  host_idna = conn->account.host;
# endif

  if (!option(OPTNOCURSES))
    mutt_message (_("Looking up %s..."), conn->account.host);

  he = gethostbyname (host_idna);

# ifdef HAVE_LIBIDN
    FREE (&host_idna);
# endif

  if (! he) {
    mutt_error (_("Could not find the host \"%s\""), conn->account.host);
	
    return -1;
  }

  if (!option(OPTNOCURSES))
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
        fcntl (fd, F_SETFD, FD_CLOEXEC);
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