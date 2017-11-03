static void ssl_get_client_cert(sslsockdata *ssldata, CONNECTION *conn)
{
  if (SslClientCert)
  {
    dprint (2, (debugfile, "Using client certificate %s\n", SslClientCert));
    SSL_CTX_set_default_passwd_cb_userdata(ssldata->ctx, &conn->account);
    SSL_CTX_set_default_passwd_cb(ssldata->ctx, ssl_passwd_cb);
    SSL_CTX_use_certificate_file(ssldata->ctx, SslClientCert, SSL_FILETYPE_PEM);
    SSL_CTX_use_PrivateKey_file(ssldata->ctx, SslClientCert, SSL_FILETYPE_PEM);

    /* if we are using a client cert, SASL may expect an external auth name */
    mutt_account_getuser (&conn->account);
  }
}