static int memcached_query_daemon (char *buffer, size_t buffer_size, memcached_t *st)
{
  int fd, status;
  size_t buffer_fill;

  fd = memcached_connect (st);
  if (fd < 0) {
    ERROR ("memcached plugin: Instance \"%s\" could not connect to daemon.",
        st->name);
    return -1;
  }

  status = (int) swrite (fd, "stats\r\n", strlen ("stats\r\n"));
  if (status != 0)
  {
    char errbuf[1024];
    ERROR ("memcached plugin: write(2) failed: %s",
        sstrerror (errno, errbuf, sizeof (errbuf)));
    shutdown(fd, SHUT_RDWR);
    close (fd);
    return (-1);
  }

  /* receive data from the memcached daemon */
  memset (buffer, 0, buffer_size);

  buffer_fill = 0;
  while ((status = (int) recv (fd, buffer + buffer_fill,
          buffer_size - buffer_fill, /* flags = */ 0)) != 0)
  {
    char const end_token[5] = {'E', 'N', 'D', '\r', '\n'};
    if (status < 0)
    {
      char errbuf[1024];

      if ((errno == EAGAIN) || (errno == EINTR))
          continue;

      ERROR ("memcached: Error reading from socket: %s",
          sstrerror (errno, errbuf, sizeof (errbuf)));
      shutdown(fd, SHUT_RDWR);
      close (fd);
      return (-1);
    }

    buffer_fill += (size_t) status;
    if (buffer_fill > buffer_size)
    {
      buffer_fill = buffer_size;
      WARNING ("memcached plugin: Message was truncated.");
      break;
    }

    /* If buffer ends in end_token, we have all the data. */
    if (memcmp (buffer + buffer_fill - sizeof (end_token),
          end_token, sizeof (end_token)) == 0)
      break;
  } /* while (recv) */

  status = 0;
  if (buffer_fill == 0)
  {
    WARNING ("memcached plugin: No data returned by memcached.");
    status = -1;
  }

  shutdown(fd, SHUT_RDWR);
  close(fd);
  return (status);
}