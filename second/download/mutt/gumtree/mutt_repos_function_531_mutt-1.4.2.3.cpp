static int ssl_socket_write (CONNECTION* conn, const char* buf, size_t len)
{
  sslsockdata *data = conn->sockdata;
  return SSL_write (data->ssl, buf, len);
}