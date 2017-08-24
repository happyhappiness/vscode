{
#if defined(__APPLE__)
  int enable;
#endif

  if (!(stream->io_watcher.fd == -1 || stream->io_watcher.fd == fd))
    return -EBUSY;

  assert(fd >= 0);
  stream->flags |= flags;

  if (stream->type == UV_TCP) {
    if ((stream->flags & UV_TCP_NODELAY) && uv__tcp_nodelay(fd, 1))
      return -errno;

    /* TODO Use delay the user passed in. */
    if ((stream->flags & UV_TCP_KEEPALIVE) && uv__tcp_keepalive(fd, 1, 60))
      return -errno;
  }

#if defined(__APPLE__)
  enable = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_OOBINLINE, &enable, sizeof(enable)) &&
      errno != ENOTSOCK &&
      errno != EINVAL) {
    return -errno;
  }
#endif

  stream->io_watcher.fd = fd;

  return 0;
}