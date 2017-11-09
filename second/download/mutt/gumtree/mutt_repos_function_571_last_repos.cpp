int raw_socket_close (CONNECTION *conn)
{
  return close (conn->fd);
}