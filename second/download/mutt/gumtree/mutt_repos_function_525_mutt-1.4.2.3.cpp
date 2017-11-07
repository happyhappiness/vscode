int mutt_ssl_starttls (CONNECTION* conn)
{
  sslsockdata* ssldata;
  int maxbits;

  if (ssl_init())
    goto bail;

  ssldata = (sslsockdata*) safe_calloc (1, sizeof (sslsockdata));
  /* the ssl_use_xxx protocol options don't apply. We must use TLS in TLS. */
  if (! (ssldata->ctx = SSL_CTX_new (TLSv1_client_method ())))
  {
    dprint (1, (debugfile, "mutt_ssl_starttls: Error allocating SSL_CTX\n"));
    goto bail_ssldata;
  }

  if (! (ssldata->ssl = SSL_new (ssldata->ctx)))
  {
    dprint (1, (debugfile, "mutt_ssl_starttls: Error allocating SSL\n"));
    goto bail_ctx;
  }

  if (SSL_set_fd (ssldata->ssl, conn->fd) != 1)
  {
    dprint (1, (debugfile, "mutt_ssl_starttls: Error setting fd\n"));
    goto bail_ssl;
  }

  if (ssl_negotiate (ssldata))
    goto bail_ssl;

  /* hmm. watch out if we're starting TLS over any method other than raw. */
  conn->sockdata = ssldata;
  conn->read = ssl_socket_read;
  conn->write = ssl_socket_write;
  conn->close = tls_close;

  conn->ssf = SSL_CIPHER_get_bits (SSL_get_current_cipher (ssldata->ssl),
    &maxbits);

  return 0;

 bail_ssl:
  FREE (&ssldata->ssl);
 bail_ctx:
  FREE (&ssldata->ctx);
 bail_ssldata:
  FREE (&ssldata);
 bail:
  return -1;
}