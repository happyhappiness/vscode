{
  int err;
  int on;

  /* Cannot set IPv6-only mode on non-IPv6 socket. */
  if ((flags & UV_TCP_IPV6ONLY) && addr->sa_family != AF_INET6)
    return -EINVAL;

  err = maybe_new_socket(tcp,
                         addr->sa_family,
                         UV_STREAM_READABLE | UV_STREAM_WRITABLE);
  if (err)
    return err;

  on = 1;
  if (setsockopt(tcp->io_watcher.fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
    return -errno;

#ifdef IPV6_V6ONLY
  if (addr->sa_family == AF_INET6) {
    on = (flags & UV_TCP_IPV6ONLY) != 0;
    if (setsockopt(tcp->io_watcher.fd,
                   IPPROTO_IPV6,
                   IPV6_V6ONLY,
                   &on,
                   sizeof on) == -1) {
#if defined(__MVS__)
      if (errno == EOPNOTSUPP)
        return -EINVAL;
#endif
      return -errno;
    }
  }
#endif

  errno = 0;
  if (bind(tcp->io_watcher.fd, addr, addrlen) && errno != EADDRINUSE) {
    if (errno == EAFNOSUPPORT)
      /* OSX, other BSDs and SunoS fail with EAFNOSUPPORT when binding a
       * socket created with AF_INET to an AF_INET6 address or vice versa. */
      return -EINVAL;
    return -errno;
  }
  tcp->delayed_error = -errno;

  tcp->flags |= UV_HANDLE_BOUND;
  if (addr->sa_family == AF_INET6)
    tcp->flags |= UV_HANDLE_IPV6;

  return 0;
}