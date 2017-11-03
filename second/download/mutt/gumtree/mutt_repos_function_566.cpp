int raw_socket_read (CONNECTION* conn, char* buf, size_t len)
{
  int rc;

  if ((rc = read (conn->fd, buf, len)) == -1)
  {
    mutt_error (_("Error talking to %s (%s)"), conn->account.host,
		strerror (errno));
    mutt_sleep (2);
  }

  return rc;
}