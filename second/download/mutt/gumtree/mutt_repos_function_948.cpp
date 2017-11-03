static int tls_socket_open (CONNECTION* conn)
{
  if (raw_socket_open (conn) < 0)
    return -1;

  if (tls_negotiate (conn) < 0)
  {
    tls_socket_close (conn);
    return -1;
  }

  return 0;
}