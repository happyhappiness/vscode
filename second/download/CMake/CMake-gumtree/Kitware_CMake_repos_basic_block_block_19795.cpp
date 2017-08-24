{
    struct sockaddr_storage saddr;
    socklen_t slen  = sizeof(saddr);
    memset(&saddr, 0, sizeof(saddr));

    if (getsockname(tcp->io_watcher.fd, (struct sockaddr*) &saddr, &slen))
      return -errno;

    if (bind(tcp->io_watcher.fd, (struct sockaddr*) &saddr, slen))
      return -errno;

    tcp->flags |= UV_HANDLE_BOUND;
  }