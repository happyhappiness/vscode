int mutt_socket_write_d (CONNECTION *conn, const char *buf, int len, int dbg)
{
  int rc;
  int sent = 0;

  dprint (dbg, (debugfile,"%d> %s", conn->fd, buf));

  if (conn->fd < 0)
  {
    dprint (1, (debugfile, "mutt_socket_write: attempt to write to closed connection\n"));
    return -1;
  }

  if (len < 0)
    len = mutt_strlen (buf);
  
  while (sent < len)
  {
    if ((rc = conn->conn_write (conn, buf + sent, len - sent)) < 0)
    {
      dprint (1, (debugfile,
                  "mutt_socket_write: error writing (%s), closing socket\n",
                  strerror(errno)));
      mutt_socket_close (conn);

      return -1;
    }

    if (rc < len - sent)
      dprint (3, (debugfile,
                  "mutt_socket_write: short write (%d of %d bytes)\n", rc,
                  len - sent));
    
    sent += rc;
  }

  return sent;
}