{
  static int single_accept = -1;
  int err;

  if (tcp->delayed_error)
    return tcp->delayed_error;

  if (single_accept == -1) {
    const char* val = getenv("UV_TCP_SINGLE_ACCEPT");
    single_accept = (val != NULL && atoi(val) != 0);  /* Off by default. */
  }

  if (single_accept)
    tcp->flags |= UV_TCP_SINGLE_ACCEPT;

  err = maybe_new_socket(tcp, AF_INET, UV_STREAM_READABLE);
  if (err)
    return err;

#ifdef __MVS__
  /* on zOS the listen call does not bind automatically
     if the socket is unbound. Hence the manual binding to
     an arbitrary port is required to be done manually
  */

  if (!(tcp->flags & UV_HANDLE_BOUND)) {
    struct sockaddr_storage saddr;
    socklen_t slen  = sizeof(saddr);
    memset(&saddr, 0, sizeof(saddr));

    if (getsockname(tcp->io_watcher.fd, (struct sockaddr*) &saddr, &slen))
      return -errno;

    if (bind(tcp->io_watcher.fd, (struct sockaddr*) &saddr, slen))
      return -errno;

    tcp->flags |= UV_HANDLE_BOUND;
  }
#endif

  if (listen(tcp->io_watcher.fd, backlog))
    return -errno;

  tcp->connection_cb = cb;
  tcp->flags |= UV_HANDLE_BOUND;

  /* Start listening for connections. */
  tcp->io_watcher.cb = uv__server_io;
  uv__io_start(tcp->loop, &tcp->io_watcher, POLLIN);

  return 0;
}