static void statsd_network_read(int fd) /* {{{ */
{
  char buffer[4096];
  size_t buffer_size;
  ssize_t status;

  status = recv(fd, buffer, sizeof(buffer), /* flags = */ MSG_DONTWAIT);
  if (status < 0) {
    char errbuf[1024];

    if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
      return;

    ERROR("statsd plugin: recv(2) failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return;
  }

  buffer_size = (size_t)status;
  if (buffer_size >= sizeof(buffer))
    buffer_size = sizeof(buffer) - 1;
  buffer[buffer_size] = 0;

  statsd_parse_buffer(buffer);
}