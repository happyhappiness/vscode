static int memcached_connect_inet(memcached_t *st) {
  struct addrinfo *ai_list;
  int fd = -1;

  struct addrinfo ai_hints = {.ai_family = AF_UNSPEC,
                              .ai_flags = AI_ADDRCONFIG,
                              .ai_socktype = SOCK_STREAM};

  int status = getaddrinfo(st->connhost, st->connport, &ai_hints, &ai_list);
  if (status != 0) {
    char errbuf[1024];
    ERROR("memcached plugin: memcached_connect_inet: "
          "getaddrinfo(%s,%s) failed: %s",
          st->connhost, st->connport,
          (status == EAI_SYSTEM) ? sstrerror(errno, errbuf, sizeof(errbuf))
                                 : gai_strerror(status));
    return -1;
  }

  for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL;
       ai_ptr = ai_ptr->ai_next) {
    /* create our socket descriptor */
    fd = socket(ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
    if (fd < 0) {
      char errbuf[1024];
      WARNING("memcached plugin: memcached_connect_inet: "
              "socket(2) failed: %s",
              sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    }

    /* switch socket to non-blocking mode */
    int flags = fcntl(fd, F_GETFL);
    status = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    if (status != 0) {
      close(fd);
      fd = -1;
      continue;
    }

    /* connect to the memcached daemon */
    status = (int)connect(fd, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
    if (status != 0 && errno != EINPROGRESS) {
      shutdown(fd, SHUT_RDWR);
      close(fd);
      fd = -1;
      continue;
    }

    /* Wait until connection establishes */
    struct pollfd pollfd = {
        .fd = fd, .events = POLLOUT,
    };
    do
      status = poll(&pollfd, 1, MEMCACHED_CONNECT_TIMEOUT);
    while (status < 0 && errno == EINTR);
    if (status <= 0) {
      close(fd);
      fd = -1;
      continue;
    }

    /* Check if all is good */
    int socket_error;
    status = getsockopt(fd, SOL_SOCKET, SO_ERROR, (void *)&socket_error,
                        &(socklen_t){sizeof(socket_error)});
    if (status != 0 || socket_error != 0) {
      close(fd);
      fd = -1;
      continue;
    }
    /* A socket is opened and connection succeeded. We're done. */
    break;
  }

  freeaddrinfo(ai_list);
  return fd;
}