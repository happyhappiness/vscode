static int tunnel_socket_poll (CONNECTION* conn, time_t wait_secs)
{
  TUNNEL_DATA* tunnel = (TUNNEL_DATA*) conn->sockdata;
  int ofd;
  int rc;

  ofd = conn->fd;
  conn->fd = tunnel->readfd;
  rc = raw_socket_poll (conn, wait_secs);
  conn->fd = ofd;

  return rc;
}