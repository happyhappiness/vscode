static int ssl_socket_close (CONNECTION * conn)
{
  sslsockdata *data = conn->sockdata;
  if (data)
  {
    if (data->isopen)
      SSL_shutdown (data->ssl);

    /* hold onto this for the life of mutt, in case we want to reconnect.
     * The purist in me wants a mutt_exit hook. */
#if 0
    X509_free (data->cert);
#endif
    SSL_free (data->ssl);
    SSL_CTX_free (data->ctx);
    FREE (&conn->sockdata);
  }

  return raw_socket_close (conn);
}