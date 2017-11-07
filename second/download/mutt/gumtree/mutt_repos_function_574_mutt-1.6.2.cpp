int mutt_tunnel_socket_setup (CONNECTION *conn)
{
  conn->conn_open = tunnel_socket_open;
  conn->conn_close = tunnel_socket_close;
  conn->conn_read = tunnel_socket_read;
  conn->conn_write = tunnel_socket_write;
  conn->conn_poll = tunnel_socket_poll;

  return 0;
}