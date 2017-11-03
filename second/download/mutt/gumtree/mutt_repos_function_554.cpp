int mutt_socket_read (CONNECTION* conn, char* buf, size_t len)
{
  int rc;

  if (conn->fd < 0)
  {
    dprint (1, (debugfile, "mutt_socket_read: attempt to read from closed connection\n"));
    return -1;
  }

  rc = conn->conn_read (conn, buf, len);
  /* EOF */
  if (rc == 0)
  {
    mutt_error (_("Connection to %s closed"), conn->account.host);
    mutt_sleep (2);
  }
  if (rc <= 0)
    mutt_socket_close (conn);

  return rc;
}