int mutt_socket_close (CONNECTION* conn)
{
  int rc = -1;

  if (conn->fd < 0)
    dprint (1, (debugfile, "mutt_socket_close: Attempt to close closed connection.\n"));
  else
    rc = conn->conn_close (conn);

  conn->fd = -1;
  conn->ssf = 0;

  return rc;
}