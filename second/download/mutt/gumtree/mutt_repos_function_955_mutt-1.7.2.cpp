static int tls_starttls_close (CONNECTION* conn)
{
  int rc;

  rc = tls_socket_close (conn);
  conn->conn_read = raw_socket_read;
  conn->conn_write = raw_socket_write;
  conn->conn_close = raw_socket_close;

  return rc;
}