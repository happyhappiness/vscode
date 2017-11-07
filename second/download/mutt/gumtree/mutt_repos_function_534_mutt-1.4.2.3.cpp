static int ssl_socket_close (CONNECTION * conn)
{
  sslsockdata *data = conn->sockdata;
  if (data)
  {
    SSL_shutdown (data->ssl);

    X509_free (data->cert);
    SSL_free (data->ssl);
    SSL_CTX_free (data->ctx);
    safe_free ((void **) &conn->sockdata);
  }

  return raw_socket_close (conn);
}