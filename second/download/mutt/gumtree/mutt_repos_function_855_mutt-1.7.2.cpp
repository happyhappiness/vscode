static int ssl_socket_read (CONNECTION* conn, char* buf, size_t len)
{
  sslsockdata *data = conn->sockdata;
  int rc;

  rc = SSL_read (data->ssl, buf, len);
  if (rc <= 0)
  {
    data->isopen = 0;
    ssl_err (data, rc);
  }

  return rc;
}