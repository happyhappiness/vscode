int raw_socket_write (CONNECTION* conn, const char* buf, size_t count)
{
  int rc;

  if ((rc = write (conn->fd, buf, count)) == -1)
  {
    mutt_error (_("Error talking to %s (%s)"), conn->account.host,
		strerror (errno));
    mutt_sleep (2);
  }

  return rc;
}