static int tunnel_socket_poll (CONNECTION* conn)
{
  TUNNEL_DATA* tunnel = (TUNNEL_DATA*) conn->sockdata;
  int ofd;
  int rc;

  ofd = conn->fd;
  conn->fd = tunnel->readfd;
  rc = raw_socket_poll (conn);
  conn->fd = ofd;

  return rc;
}