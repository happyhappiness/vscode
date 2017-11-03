static int ssl_socket_open (CONNECTION * conn)
{
  sslsockdata *data;
  int maxbits;

  if (raw_socket_open (conn) < 0)
    return -1;

  data = (sslsockdata *) safe_calloc (1, sizeof (sslsockdata));
  conn->sockdata = data;

  if (! (data->ctx = SSL_CTX_new (SSLv23_client_method ())))
  {
    /* L10N: an SSL context is a data structure returned by the OpenSSL
     *       function SSL_CTX_new().  In this case it returned NULL: an
     *       error condition.
     */
    mutt_error (_("Unable to create SSL context"));
    ssl_dprint_err_stack ();
    mutt_socket_close (conn);
    return -1;
  }

  /* disable SSL protocols as needed */
  if (!option(OPTTLSV1))
  {
    SSL_CTX_set_options(data->ctx, SSL_OP_NO_TLSv1);
  }
  /* TLSv1.1/1.2 support was added in OpenSSL 1.0.1, but some OS distros such
   * as Fedora 17 are on OpenSSL 1.0.0.
   */
#ifdef SSL_OP_NO_TLSv1_1
  if (!option(OPTTLSV1_1))
  {
    SSL_CTX_set_options(data->ctx, SSL_OP_NO_TLSv1_1);
  }
#endif
#ifdef SSL_OP_NO_TLSv1_2
  if (!option(OPTTLSV1_2))
  {
    SSL_CTX_set_options(data->ctx, SSL_OP_NO_TLSv1_2);
  }
#endif
  if (!option(OPTSSLV2))
  {
    SSL_CTX_set_options(data->ctx, SSL_OP_NO_SSLv2);
  }
  if (!option(OPTSSLV3))
  {
    SSL_CTX_set_options(data->ctx, SSL_OP_NO_SSLv3);
  }

  ssl_get_client_cert(data, conn);

  if (SslCiphers) {
    SSL_CTX_set_cipher_list (data->ctx, SslCiphers);
  }

  data->ssl = SSL_new (data->ctx);
  SSL_set_fd (data->ssl, conn->fd);

  if (ssl_negotiate(conn, data))
  {
    mutt_socket_close (conn);
    return -1;
  }

  data->isopen = 1;

  conn->ssf = SSL_CIPHER_get_bits (SSL_get_current_cipher (data->ssl),
    &maxbits);

  return 0;
}