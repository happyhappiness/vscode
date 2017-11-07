static int check_certificate_by_signer (X509 *peercert)
{
  X509_STORE_CTX *xsc;
  X509_STORE *ctx;
  int pass = 0, i;

  ctx = X509_STORE_new ();
  if (ctx == NULL) return 0;

  if (option (OPTSSLSYSTEMCERTS))
  {
    if (X509_STORE_set_default_paths (ctx))
      pass++;
    else
      dprint (2, (debugfile, "X509_STORE_set_default_paths failed\n"));
  }

  if (X509_STORE_load_locations (ctx, SslCertFile, NULL))
    pass++;
  else
    dprint (2, (debugfile, "X509_STORE_load_locations failed\n"));

  for (i = 0; i < sk_X509_num (SslSessionCerts); i++)
    pass += (X509_STORE_add_cert (ctx, sk_X509_value (SslSessionCerts, i)) != 0);

  if (pass == 0)
  {
    /* nothing to do */
    X509_STORE_free (ctx);
    return 0;
  }

  xsc = X509_STORE_CTX_new();
  if (xsc == NULL) return 0;
  X509_STORE_CTX_init (xsc, ctx, peercert, SslSessionCerts);

  pass = (X509_verify_cert (xsc) > 0);
#ifdef DEBUG
  if (! pass)
  {
    char buf[SHORT_STRING];
    int err;

    err = X509_STORE_CTX_get_error (xsc);
    snprintf (buf, sizeof (buf), "%s (%d)",
	X509_verify_cert_error_string(err), err);
    dprint (2, (debugfile, "X509_verify_cert: %s\n", buf));
  }
#endif
  X509_STORE_CTX_free (xsc);
  X509_STORE_free (ctx);

  return pass;
}