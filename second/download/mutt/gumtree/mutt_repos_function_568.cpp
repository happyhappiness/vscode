int raw_socket_poll (CONNECTION* conn)
{
  fd_set rfds;
  struct timeval tv = { 0, 0 };

  if (conn->fd < 0)
    return -1;

  FD_ZERO (&rfds);
  FD_SET (conn->fd, &rfds);
  
  return select (conn->fd + 1, &rfds, NULL, NULL, &tv);
}