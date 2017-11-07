int ssl_socket_setup (CONNECTION * conn)
{
  if (ssl_init() < 0)
  {
    conn->open = ssl_socket_open_err;
    return -1;
  }

  conn->open	= ssl_socket_open;
  conn->read	= ssl_socket_read;
  conn->write	= ssl_socket_write;
  conn->close	= ssl_socket_close;

  return 0;
}