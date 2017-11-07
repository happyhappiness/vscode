int mutt_socket_write_d (CONNECTION *conn, const char *buf, int dbg)
{
  int rc;
  int len;

  dprint (dbg, (debugfile,"> %s", buf));

  if (conn->fd < 0)
  {
    dprint (1, (debugfile, "mutt_socket_write: attempt to write to closed connection\n"));
    return -1;
  }

  len = mutt_strlen (buf);
  if ((rc = conn->write (conn, buf, len)) < 0)
  {
    dprint (1, (debugfile,
      "mutt_socket_write: error writing, closing socket\n"));
    mutt_socket_close (conn);

    return -1;
  }

  if (rc < len)
  {
    dprint (1, (debugfile,
      "mutt_socket_write: ERROR: wrote %d of %d bytes!\n", rc, len));
  }

  return rc;
}