static int ssl_socket_read (CONNECTION* conn, char* buf, size_t len)
{
  sslsockdata *data = conn->sockdata;
  return SSL_read (data->ssl, buf, len);
}