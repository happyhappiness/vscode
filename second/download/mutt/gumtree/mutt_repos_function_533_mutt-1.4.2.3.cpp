int ssl_negotiate (sslsockdata* ssldata)
{
  int err;
  const char* errmsg;

#if OPENSSL_VERSION_NUMBER >= 0x00906000L
  /* This only exists in 0.9.6 and above. Without it we may get interrupted
   *   reads or writes. Bummer. */
  SSL_set_mode (ssldata->ssl, SSL_MODE_AUTO_RETRY);
#endif

  if ((err = SSL_connect (ssldata->ssl)) != 1)
  {
    switch (SSL_get_error (ssldata->ssl, err))
    {
    case SSL_ERROR_SYSCALL:
      errmsg = _("I/O error");
      break;
    case SSL_ERROR_SSL:
      errmsg = _("unspecified protocol error");
      break;
    default:
      errmsg = _("unknown error");
    }
    
    mutt_error (_("SSL failed: %s"), errmsg);
    mutt_sleep (1);

    return -1;
  }

  ssldata->cert = SSL_get_peer_certificate (ssldata->ssl);
  if (!ssldata->cert)
  {
    mutt_error (_("Unable to get certificate from peer"));
    mutt_sleep (1);
    return -1;
  }

  if (!ssl_check_certificate (ssldata))
    return -1;

  mutt_message (_("SSL connection using %s (%s)"), 
    SSL_get_cipher_version (ssldata->ssl), SSL_get_cipher_name (ssldata->ssl));
  mutt_sleep (0);

  return 0;
}