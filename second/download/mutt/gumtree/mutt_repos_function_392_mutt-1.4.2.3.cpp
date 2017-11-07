int mutt_tunnel_socket_setup (CONNECTION *conn)
{
  conn->open = tunnel_socket_open;
  conn->close = tunnel_socket_close;
  conn->read = tunnel_socket_read;
  conn->write = tunnel_socket_write;

  return 0;
}