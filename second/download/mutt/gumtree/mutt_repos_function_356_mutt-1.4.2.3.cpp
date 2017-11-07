int mutt_socket_open (CONNECTION* conn) 
{
  if (socket_preconnect ())
    return -1;

  return conn->open (conn);
}