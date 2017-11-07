static int tls_close (CONNECTION* conn)
{
  int rc;

  rc = ssl_socket_close (conn);
  conn->read = raw_socket_read;
  conn->write = raw_socket_write;
  conn->close = raw_socket_close;

  return rc;
}