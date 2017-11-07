static int ssl_socket_open (CONNECTION * conn)
{
  sslsockdata *data;
  int maxbits;

  if (raw_socket_open (conn) < 0)
    return -1;

  data = (sslsockdata *) safe_calloc (1, sizeof (sslsockdata));
  conn->sockdata = data;

  data->ctx = SSL_CTX_new (SSLv23_client_method ());

  /* disable SSL protocols as needed */
  if (!option(OPTTLSV1)) 
  {
    SSL_CTX_set_options(data->ctx, SSL_OP_NO_TLSv1);
  }
  if (!option(OPTSSLV2)) 
  {
    SSL_CTX_set_options(data->ctx, SSL_OP_NO_SSLv2);
  }
  if (!option(OPTSSLV3)) 
  {
    SSL_CTX_set_options(data->ctx, SSL_OP_NO_SSLv3);
  }

  data->ssl = SSL_new (data->ctx);
  SSL_set_fd (data->ssl, conn->fd);

  if (ssl_negotiate(data))
  {
    ssl_socket_close (conn);
    return -1;
  }
  
  conn->ssf = SSL_CIPHER_get_bits (SSL_get_current_cipher (data->ssl),
    &maxbits);

  return 0;
}