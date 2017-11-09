static int ssl_load_certificates (SSL_CTX *ctx)
{
  FILE *fp;
  X509 *cert = NULL;
  X509_STORE *store;
  char buf[STRING];
  int rv = 1;

  dprint (2, (debugfile, "ssl_load_certificates: loading trusted certificates\n"));
  store = SSL_CTX_get_cert_store (ctx);
  if (!store)
  {
    store = X509_STORE_new ();
    SSL_CTX_set_cert_store (ctx, store);
  }

  if ((fp = fopen (SslCertFile, "rt")) == NULL)
    return 0;

  while (NULL != PEM_read_X509 (fp, &cert, NULL, NULL))
  {
    if ((X509_cmp_current_time (X509_get_notBefore (cert)) >= 0) ||
        (X509_cmp_current_time (X509_get_notAfter (cert)) <= 0))
    {
      dprint (2, (debugfile, "ssl_load_certificates: filtering expired cert: %s\n",
              X509_NAME_oneline (X509_get_subject_name (cert), buf, sizeof (buf))));
    }
    else
    {
      X509_STORE_add_cert (store, cert);
    }
  }
  /* PEM_read_X509 sets the error NO_START_LINE on eof */
  if (ERR_GET_REASON(ERR_peek_last_error()) != PEM_R_NO_START_LINE)
    rv = 0;
  ERR_clear_error();

  X509_free (cert);
  safe_fclose (&fp);

  return rv;
}