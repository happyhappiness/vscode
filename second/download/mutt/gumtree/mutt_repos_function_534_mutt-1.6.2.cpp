int mutt_socket_open (CONNECTION* conn) 
{
  int rc;

  if (socket_preconnect ())
    return -1;

  rc = conn->conn_open (conn);

  dprint (2, (debugfile, "Connected to %s:%d on fd=%d\n",
	      NONULL (conn->account.host), conn->account.port, conn->fd));

  return rc;
}