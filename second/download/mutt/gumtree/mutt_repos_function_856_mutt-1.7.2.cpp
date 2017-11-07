static int ssl_socket_write (CONNECTION* conn, const char* buf, size_t len)
{
  sslsockdata *data = conn->sockdata;
  int rc;

  rc = SSL_write (data->ssl, buf, len);
  if (rc <= 0)
    ssl_err (data, rc);

  return rc;
}