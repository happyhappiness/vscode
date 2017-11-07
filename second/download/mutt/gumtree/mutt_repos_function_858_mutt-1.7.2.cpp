static int ssl_negotiate (CONNECTION *conn, sslsockdata* ssldata)
{
  int err;
  const char* errmsg;

  SSL_set_mode (ssldata->ssl, SSL_MODE_AUTO_RETRY);

  if ((err = SSL_connect (ssldata->ssl)) != 1)
  {
    switch (SSL_get_error (ssldata->ssl, err))
    {
    case SSL_ERROR_SYSCALL:
      errmsg = _("I/O error");
      break;
    case SSL_ERROR_SSL:
      errmsg = ERR_error_string (ERR_get_error (), NULL);
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

  if (!ssl_check_certificate (conn, ssldata))
    return -1;

  /* L10N:
     %1$s is version (e.g. "TLSv1.2")
     %2$s is cipher_version (e.g. "TLSv1/SSLv3")
     %3$s is cipher_name (e.g. "ECDHE-RSA-AES128-GCM-SHA256") */
  mutt_message (_("%s connection using %s (%s)"),
    SSL_get_version(ssldata->ssl), SSL_get_cipher_version (ssldata->ssl), SSL_get_cipher_name (ssldata->ssl));
  mutt_sleep (0);

  return 0;
}