static void tls_get_client_cert (CONNECTION* conn)
{
  tlssockdata *data = conn->sockdata;
  const gnutls_datum_t* crtdata;
  gnutls_x509_crt_t clientcrt;
  char* dn;
  char* cn;
  char* cnend;
  size_t dnlen;

  /* get our cert CN if we have one */
  if (!(crtdata = gnutls_certificate_get_ours (data->state)))
    return;

  if (gnutls_x509_crt_init (&clientcrt) < 0)
  {
    dprint (1, (debugfile, "Failed to init gnutls crt\n"));
    return;
  }
  if (gnutls_x509_crt_import (clientcrt, crtdata, GNUTLS_X509_FMT_DER) < 0)
  {
    dprint (1, (debugfile, "Failed to import gnutls client crt\n"));
    goto err_crt;
  }
  /* get length of DN */
  dnlen = 0;
  gnutls_x509_crt_get_dn (clientcrt, NULL, &dnlen);
  if (!(dn = calloc (1, dnlen)))
  {
    dprint (1, (debugfile, "could not allocate DN\n"));
    goto err_crt;
  }
  gnutls_x509_crt_get_dn (clientcrt, dn, &dnlen);
  dprint (2, (debugfile, "client certificate DN: %s\n", dn));

  /* extract CN to use as external user name */
  if (!(cn = strstr (dn, "CN=")))
  {
    dprint (1, (debugfile, "no CN found in DN\n"));
    goto err_dn;
  }
  cn += 3;

  if ((cnend = strstr (dn, ",EMAIL=")))
    *cnend = '\0';

  /* if we are using a client cert, SASL may expect an external auth name */
  mutt_account_getuser (&conn->account);

err_dn:
  FREE (&dn);
err_crt:
  gnutls_x509_crt_deinit (clientcrt);
}