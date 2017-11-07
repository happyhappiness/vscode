static int tls_socket_read (CONNECTION* conn, char* buf, size_t len)
{
  tlssockdata *data = conn->sockdata;
  int ret;

  if (!data)
  {
    mutt_error (_("Error: no TLS socket open"));
    mutt_sleep (2);
    return -1;
  }

  do {
    ret = gnutls_record_recv (data->state, buf, len);
    if (ret < 0 && gnutls_error_is_fatal(ret) == 1)
    {
      mutt_error ("tls_socket_read (%s)", gnutls_strerror (ret));
      mutt_sleep (4);
      return -1;
    }
  }
  while (ret == GNUTLS_E_AGAIN || ret == GNUTLS_E_INTERRUPTED);

  return ret;
}