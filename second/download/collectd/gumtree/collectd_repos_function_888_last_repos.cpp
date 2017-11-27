static int memcached_query_daemon(char *buffer, size_t buffer_size,
                                  memcached_t *st) {
  int status;
  size_t buffer_fill;

  memcached_connect(st);
  if (st->fd < 0) {
    ERROR("memcached plugin: Instance \"%s\" could not connect to daemon.",
          st->name);
    return -1;
  }

  struct pollfd pollfd = {
      .fd = st->fd, .events = POLLOUT,
  };

  do
    status = poll(&pollfd, 1, MEMCACHED_IO_TIMEOUT);
  while (status < 0 && errno == EINTR);

  if (status <= 0) {
    ERROR("memcached plugin: poll() failed for write() call.");
    close(st->fd);
    st->fd = -1;
    return -1;
  }

  status = (int)swrite(st->fd, "stats\r\n", strlen("stats\r\n"));
  if (status != 0) {
    char errbuf[1024];
    ERROR("memcached plugin: Instance \"%s\": write(2) failed: %s", st->name,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    shutdown(st->fd, SHUT_RDWR);
    close(st->fd);
    st->fd = -1;
    return -1;
  }

  /* receive data from the memcached daemon */
  memset(buffer, 0, buffer_size);

  buffer_fill = 0;
  pollfd.events = POLLIN;
  while (1) {
    do
      status = poll(&pollfd, 1, MEMCACHED_IO_TIMEOUT);
    while (status < 0 && errno == EINTR);

    if (status <= 0) {
      ERROR("memcached plugin: Instance \"%s\": Timeout reading from socket",
            st->name);
      close(st->fd);
      st->fd = -1;
      return -1;
    }

    do
      status = (int)recv(st->fd, buffer + buffer_fill,
                         buffer_size - buffer_fill, /* flags = */ 0);
    while (status < 0 && errno == EINTR);

    char const end_token[5] = {'E', 'N', 'D', '\r', '\n'};
    if (status < 0) {
      char errbuf[1024];

      if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
        continue;

      ERROR("memcached plugin: Instance \"%s\": Error reading from socket: %s",
            st->name, sstrerror(errno, errbuf, sizeof(errbuf)));
      shutdown(st->fd, SHUT_RDWR);
      close(st->fd);
      st->fd = -1;
      return -1;
    }

    buffer_fill += (size_t)status;
    if (buffer_fill > buffer_size) {
      buffer_fill = buffer_size;
      WARNING("memcached plugin: Instance \"%s\": Message was truncated.",
              st->name);
      shutdown(st->fd, SHUT_RDWR);
      close(st->fd);
      st->fd = -1;
      break;
    }

    /* If buffer ends in end_token, we have all the data. */
    if (memcmp(buffer + buffer_fill - sizeof(end_token), end_token,
               sizeof(end_token)) == 0)
      break;
  } /* while (recv) */

  status = 0;
  if (buffer_fill == 0) {
    WARNING("memcached plugin: Instance \"%s\": No data returned by memcached.",
            st->name);
    status = -1;
  }

  return status;
}