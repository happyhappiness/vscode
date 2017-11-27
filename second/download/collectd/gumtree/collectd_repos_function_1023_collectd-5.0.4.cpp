static int pb_add_socket (pinba_socket_t *s, /* {{{ */
    const struct addrinfo *ai)
{
  int fd;
  int tmp;
  int status;

  if (s->fd_num == PINBA_MAX_SOCKETS)
  {
    WARNING ("pinba plugin: Sorry, you have hit the built-in limit of "
        "%i sockets. Please complain to the collectd developers so we can "
        "raise the limit.", PINBA_MAX_SOCKETS);
    return (-1);
  }

  fd = socket (ai->ai_family, ai->ai_socktype, ai->ai_protocol);
  if (fd < 0)
  {
    char errbuf[1024];
    ERROR ("pinba plugin: socket(2) failed: %s",
        sstrerror (errno, errbuf, sizeof (errbuf)));
    return (0);
  }

  tmp = 1;
  status = setsockopt (fd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof (tmp));
  if (status != 0)
  {
    char errbuf[1024];
    WARNING ("pinba plugin: setsockopt(SO_REUSEADDR) failed: %s",
        sstrerror (errno, errbuf, sizeof (errbuf)));
  }

  status = bind (fd, ai->ai_addr, ai->ai_addrlen);
  if (status != 0)
  {
    char errbuf[1024];
    ERROR ("pinba plugin: bind(2) failed: %s",
        sstrerror (errno, errbuf, sizeof (errbuf)));
    return (0);
  }

  s->fd[s->fd_num].fd = fd;
  s->fd[s->fd_num].events = POLLIN | POLLPRI;
  s->fd[s->fd_num].revents = 0;
  s->fd_num++;

  return (0);
}