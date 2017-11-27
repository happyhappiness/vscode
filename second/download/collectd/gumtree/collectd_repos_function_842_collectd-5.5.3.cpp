static int memcached_connect_inet (memcached_t *st)
{
  char *host;
  char *port;

  struct addrinfo  ai_hints;
  struct addrinfo *ai_list, *ai_ptr;
  int status;
  int fd = -1;

  memset (&ai_hints, 0, sizeof (ai_hints));
  ai_hints.ai_flags    = 0;
#ifdef AI_ADDRCONFIG
  ai_hints.ai_flags   |= AI_ADDRCONFIG;
#endif
  ai_hints.ai_family   = AF_UNSPEC;
  ai_hints.ai_socktype = SOCK_STREAM;
  ai_hints.ai_protocol = 0;

  host = (st->host != NULL) ? st->host : MEMCACHED_DEF_HOST;
  port = (st->port != NULL) ? st->port : MEMCACHED_DEF_PORT;

  ai_list = NULL;
  status = getaddrinfo (host, port, &ai_hints, &ai_list);
  if (status != 0)
  {
    char errbuf[1024];
    ERROR ("memcached plugin: memcached_connect_inet: "
        "getaddrinfo(%s,%s) failed: %s",
        host, port,
        (status == EAI_SYSTEM)
        ? sstrerror (errno, errbuf, sizeof (errbuf))
        : gai_strerror (status));
    return (-1);
  }

  for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
  {
    /* create our socket descriptor */
    fd = socket (ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
    if (fd < 0)
    {
      char errbuf[1024];
      WARNING ("memcached plugin: memcached_connect_inet: "
          "socket(2) failed: %s",
          sstrerror (errno, errbuf, sizeof (errbuf)));
      continue;
    }

    /* connect to the memcached daemon */
    status = (int) connect (fd, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
    if (status != 0)
    {
      shutdown (fd, SHUT_RDWR);
      close (fd);
      fd = -1;
      continue;
    }

    /* A socket could be opened and connecting succeeded. We're done. */
    break;
  }

  freeaddrinfo (ai_list);
  return (fd);
}