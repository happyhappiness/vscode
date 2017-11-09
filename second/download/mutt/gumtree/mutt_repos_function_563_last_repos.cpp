int mutt_socket_readchar (CONNECTION *conn, char *c)
{
  if (conn->bufpos >= conn->available)
  {
    if (conn->fd >= 0)
      conn->available = conn->conn_read (conn, conn->inbuf, sizeof (conn->inbuf));
    else
    {
      dprint (1, (debugfile, "mutt_socket_readchar: attempt to read from closed connection.\n"));
      return -1;
    }
    conn->bufpos = 0;
    if (conn->available == 0)
    {
      mutt_error (_("Connection to %s closed"), conn->account.host);
      mutt_sleep (2);
    }
    if (conn->available <= 0)
    {
      mutt_socket_close (conn);
      return -1;
    }
  }
  *c = conn->inbuf[conn->bufpos];
  conn->bufpos++;
  return 1;
}