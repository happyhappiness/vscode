static int ssl_negotiate (CONNECTION *conn, sslsockdata* ssldata)
{
  int err;
  const char* errmsg;

  if ((HostExDataIndex = SSL_get_ex_new_index (0, "host", NULL, NULL, NULL)) == -1)
  {
    dprint (1, (debugfile, "failed to get index for application specific data\n"));
    return -1;
  }

  if (! SSL_set_ex_data (ssldata->ssl, HostExDataIndex, conn->account.host))
  {
    dprint (1, (debugfile, "failed to save hostname in SSL structure\n"));
    return -1;
  }

  if ((SkipModeExDataIndex = SSL_get_ex_new_index (0, "skip", NULL, NULL, NULL)) == -1)
  {
    dprint (1, (debugfile, "failed to get index for application specific data\n"));
    return -1;
  }

  if (! SSL_set_ex_data (ssldata->ssl, SkipModeExDataIndex, NULL))
  {
    dprint (1, (debugfile, "failed to save skip mode in SSL structure\n"));
    return -1;
  }

  SSL_set_verify (ssldata->ssl, SSL_VERIFY_PEER, ssl_verify_callback);
  SSL_set_mode (ssldata->ssl, SSL_MODE_AUTO_RETRY);

  if (!SSL_set_tlsext_host_name (ssldata->ssl, conn->account.host))
  {
    /* L10N: This is a warning when trying to set the host name for
     * TLS Server Name Indication (SNI).  This allows the server to present
     * the correct certificate if it supports multiple hosts. */
    mutt_error _("Warning: unable to set TLS SNI host name");
    mutt_sleep (1);
  }

  ERR_clear_error ();

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

  /* L10N:
     %1$s is version (e.g. "TLSv1.2")
     %2$s is cipher_version (e.g. "TLSv1/SSLv3")
     %3$s is cipher_name (e.g. "ECDHE-RSA-AES128-GCM-SHA256") */
  mutt_message (_("%s connection using %s (%s)"),
    SSL_get_version(ssldata->ssl), SSL_get_cipher_version (ssldata->ssl), SSL_get_cipher_name (ssldata->ssl));
  mutt_sleep (0);

  return 0;
}