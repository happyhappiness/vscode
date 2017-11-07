int mutt_socket_poll (CONNECTION* conn)
{
  if (conn->bufpos < conn->available)
    return conn->available - conn->bufpos;

  if (conn->conn_poll)
    return conn->conn_poll (conn);

  return -1;
}