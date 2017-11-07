static int tls_socket_write (CONNECTION* conn, const char* buf, size_t len)
{
  tlssockdata *data = conn->sockdata;
  int ret;
  size_t sent = 0;

  if (!data)
  {
    mutt_error (_("Error: no TLS socket open"));
    mutt_sleep (2);
    return -1;
  }

  do
  {
    ret = gnutls_record_send (data->state, buf + sent, len - sent);
    if (ret < 0)
    {
      if (gnutls_error_is_fatal(ret) == 1)
      {
	mutt_error ("tls_socket_write (%s)", gnutls_strerror (ret));
	mutt_sleep (4);
	return -1;
      }
      return ret;
    }
    sent += ret;
  } while (sent < len);

  return sent;
}