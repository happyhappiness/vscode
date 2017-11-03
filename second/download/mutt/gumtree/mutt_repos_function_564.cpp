static CONNECTION* socket_new_conn (void)
{
  CONNECTION* conn;

  conn = (CONNECTION *) safe_calloc (1, sizeof (CONNECTION));
  conn->fd = -1;

  return conn;
}