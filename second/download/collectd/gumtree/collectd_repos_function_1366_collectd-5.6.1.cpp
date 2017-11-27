static int create_sockets (socket_entry_t **ret_sockets, /* {{{ */
    size_t *ret_sockets_num,
    const char *node, const char *service, int listen)
{
  struct addrinfo *ai_list;
  int              ai_return;

  socket_entry_t *sockets = NULL;
  size_t          sockets_num = 0;

  int status;

  if (*ret_sockets != NULL)
    return (EINVAL);

  struct addrinfo ai_hints = {
    .ai_family = AF_UNSPEC,
    .ai_flags = AI_ADDRCONFIG | AI_PASSIVE,
    .ai_protocol = IPPROTO_UDP,
    .ai_socktype = SOCK_DGRAM
  };

  ai_return = getaddrinfo (node, service, &ai_hints, &ai_list);
  if (ai_return != 0)
  {
    char errbuf[1024];
    ERROR ("gmond plugin: getaddrinfo (%s, %s) failed: %s",
        (node == NULL) ? "(null)" : node,
        (service == NULL) ? "(null)" : service,
        (ai_return == EAI_SYSTEM)
        ? sstrerror (errno, errbuf, sizeof (errbuf))
        : gai_strerror (ai_return));
    return (-1);
  }

  for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next) /* {{{ */
  {
    socket_entry_t *tmp;

    tmp = realloc (sockets, (sockets_num + 1) * sizeof (*sockets));
    if (tmp == NULL)
    {
      ERROR ("gmond plugin: realloc failed.");
      continue;
    }
    sockets = tmp;

    sockets[sockets_num].fd = socket (ai_ptr->ai_family, ai_ptr->ai_socktype,
        ai_ptr->ai_protocol);
    if (sockets[sockets_num].fd < 0)
    {
      char errbuf[1024];
      ERROR ("gmond plugin: socket failed: %s",
          sstrerror (errno, errbuf, sizeof (errbuf)));
      continue;
    }

    assert (sizeof (sockets[sockets_num].addr) >= ai_ptr->ai_addrlen);
    memcpy (&sockets[sockets_num].addr, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
    sockets[sockets_num].addrlen = ai_ptr->ai_addrlen;

    /* Sending socket: Open only one socket and don't bind it. */
    if (listen == 0)
    {
      sockets_num++;
      break;
    }
    else
    {
      int yes = 1;

      status = setsockopt (sockets[sockets_num].fd, SOL_SOCKET, SO_REUSEADDR,
          (void *) &yes, sizeof (yes));
      if (status != 0)
      {
        char errbuf[1024];
        WARNING ("gmond plugin: setsockopt(2) failed: %s",
                 sstrerror (errno, errbuf, sizeof (errbuf)));
      }
    }

    status = bind (sockets[sockets_num].fd, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
    if (status != 0)
    {
      char errbuf[1024];
      ERROR ("gmond plugin: bind failed: %s",
          sstrerror (errno, errbuf, sizeof (errbuf)));
      close (sockets[sockets_num].fd);
      continue;
    }

    if (ai_ptr->ai_family == AF_INET)
    {
      struct sockaddr_in *addr;
      int loop;

      addr = (struct sockaddr_in *) ai_ptr->ai_addr;

      if (!IN_MULTICAST (ntohl (addr->sin_addr.s_addr)))
      {
        sockets_num++;
        continue;
      }

      loop = 1;
      status = setsockopt (sockets[sockets_num].fd, IPPROTO_IP, IP_MULTICAST_LOOP,
          (void *) &loop, sizeof (loop));
      if (status != 0)
      {
        char errbuf[1024];
        WARNING ("gmond plugin: setsockopt(2) failed: %s",
                 sstrerror (errno, errbuf, sizeof (errbuf)));
      }

      struct ip_mreq mreq = {
        .imr_multiaddr.s_addr = addr->sin_addr.s_addr,
        .imr_interface.s_addr = htonl (INADDR_ANY)
      };

      status = setsockopt (sockets[sockets_num].fd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
          (void *) &mreq, sizeof (mreq));
      if (status != 0)
      {
        char errbuf[1024];
        WARNING ("gmond plugin: setsockopt(2) failed: %s",
                 sstrerror (errno, errbuf, sizeof (errbuf)));
      }
    } /* if (ai_ptr->ai_family == AF_INET) */
    else if (ai_ptr->ai_family == AF_INET6)
    {
      struct sockaddr_in6 *addr;
      int loop;

      addr = (struct sockaddr_in6 *) ai_ptr->ai_addr;

      if (!IN6_IS_ADDR_MULTICAST (&addr->sin6_addr))
      {
        sockets_num++;
        continue;
      }

      loop = 1;
      status = setsockopt (sockets[sockets_num].fd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP,
          (void *) &loop, sizeof (loop));
      if (status != 0)
      {
        char errbuf[1024];
        WARNING ("gmond plugin: setsockopt(2) failed: %s",
                 sstrerror (errno, errbuf, sizeof (errbuf)));
      }

      struct ipv6_mreq mreq = {
        .ipv6mr_interface = 0 /* any */
      };

      memcpy (&mreq.ipv6mr_multiaddr,
          &addr->sin6_addr, sizeof (addr->sin6_addr));
      status = setsockopt (sockets[sockets_num].fd, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP,
          (void *) &mreq, sizeof (mreq));
      if (status != 0)
      {
        char errbuf[1024];
        WARNING ("gmond plugin: setsockopt(2) failed: %s",
                 sstrerror (errno, errbuf, sizeof (errbuf)));
      }
    } /* if (ai_ptr->ai_family == AF_INET6) */

    sockets_num++;
  } /* }}} for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next) */

  freeaddrinfo (ai_list);

  if (sockets_num == 0)
  {
    sfree (sockets);
    return (-1);
  }

  *ret_sockets = sockets;
  *ret_sockets_num = sockets_num;
  return (0);
}