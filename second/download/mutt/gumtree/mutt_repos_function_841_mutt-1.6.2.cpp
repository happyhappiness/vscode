static int tls_close (CONNECTION* conn)
{
  int rc;

  rc = ssl_socket_close (conn);
  conn->conn_read = raw_socket_read;
  conn->conn_write = raw_socket_write;
  conn->conn_close = raw_socket_close;

  return rc;
}