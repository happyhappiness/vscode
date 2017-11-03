int mutt_ssl_socket_setup (CONNECTION* conn)
{
  if (tls_init() < 0)
    return -1;

  conn->conn_open	= tls_socket_open;
  conn->conn_read	= tls_socket_read;
  conn->conn_write	= tls_socket_write;
  conn->conn_close	= tls_socket_close;
  conn->conn_poll       = raw_socket_poll;

  return 0;
}