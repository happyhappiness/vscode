int mutt_socket_poll (CONNECTION* conn, time_t wait_secs)
{
  if (conn->bufpos < conn->available)
    return conn->available - conn->bufpos;

  if (conn->conn_poll)
    return conn->conn_poll (conn, wait_secs);

  return -1;
}