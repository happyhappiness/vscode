static int mc_handle_socket(struct pollfd *p) /* {{{ */
{
  char buffer[BUFF_SIZE];
  ssize_t buffer_size;

  if ((p->revents & (POLLIN | POLLPRI)) == 0) {
    p->revents = 0;
    return (-1);
  }

  buffer_size = recv(p->fd, buffer, sizeof(buffer), /* flags = */ 0);
  if (buffer_size <= 0) {
    char errbuf[1024];
    ERROR("gmond plugin: recv failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    p->revents = 0;
    return (-1);
  }

  mc_handle_metric(buffer, (size_t)buffer_size);
  return (0);
}