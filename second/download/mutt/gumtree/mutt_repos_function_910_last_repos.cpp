static int ssl_verify_callback (int preverify_ok, X509_STORE_CTX *ctx)
{
  char buf[STRING];
  const char *host;
  int len, pos;
  X509 *cert;
  SSL *ssl;
  int skip_mode;
#ifdef HAVE_SSL_PARTIAL_CHAIN
  static int last_pos = 0;
  static X509 *last_cert = NULL;
  unsigned char last_cert_md[EVP_MAX_MD_SIZE];
  unsigned int last_cert_mdlen;
#endif

  if (! (ssl = X509_STORE_CTX_get_ex_data (ctx, SSL_get_ex_data_X509_STORE_CTX_idx ())))
  {
    dprint (1, (debugfile, "ssl_verify_callback: failed to retrieve SSL structure from X509_STORE_CTX\n"));
    return 0;
  }
  if (! (host = SSL_get_ex_data (ssl, HostExDataIndex)))
  {
    dprint (1, (debugfile, "ssl_verify_callback: failed to retrieve hostname from SSL structure\n"));
    return 0;
  }

  /* This is true when a previous entry in the certificate chain did
   * not verify and the user manually chose to skip it via the
   * $ssl_verify_partial_chains option.
   * In this case, all following certificates need to be treated as non-verified
   * until one is actually verified.
   */
  skip_mode = (SSL_get_ex_data (ssl, SkipModeExDataIndex) != NULL);

  cert = X509_STORE_CTX_get_current_cert (ctx);
  pos = X509_STORE_CTX_get_error_depth (ctx);
  len = sk_X509_num (X509_STORE_CTX_get_chain (ctx));

  dprint (1, (debugfile,
              "ssl_verify_callback: checking cert chain entry %s (preverify: %d skipmode: %d)\n",
              X509_NAME_oneline (X509_get_subject_name (cert), buf, sizeof (buf)),
              preverify_ok, skip_mode));

#ifdef HAVE_SSL_PARTIAL_CHAIN
  /* Sometimes, when a certificate is (s)kipped, OpenSSL will pass it
   * a second time with preverify_ok = 1.  Don't show it or the user
   * will think their "s" key is broken.
   */
  if (option (OPTSSLVERIFYPARTIAL))
  {
    if (skip_mode && preverify_ok && (pos == last_pos) && last_cert)
    {
      if (X509_digest (last_cert, EVP_sha256(), last_cert_md, &last_cert_mdlen) &&
          !compare_certificates (cert, last_cert, last_cert_md, last_cert_mdlen))
      {
        dprint (2, (debugfile,
                    "ssl_verify_callback: ignoring duplicate skipped certificate.\n"));
        return 1;
      }
    }

    last_pos = pos;
    if (last_cert)
      X509_free (last_cert);
    last_cert = X509_dup (cert);
  }
#endif

  /* check session cache first */
  if (check_certificate_cache (cert))
  {
    dprint (2, (debugfile, "ssl_verify_callback: using cached certificate\n"));
    SSL_set_ex_data (ssl, SkipModeExDataIndex, NULL);
    return 1;
  }

  /* check hostname only for the leaf certificate */
  buf[0] = 0;
  if (pos == 0 && option (OPTSSLVERIFYHOST) != MUTT_NO)
  {
    if (!check_host (cert, host, buf, sizeof (buf)))
    {
      mutt_error (_("Certificate host check failed: %s"), buf);
      mutt_sleep (2);
      /* we disallow (a)ccept always in the prompt, because it will have no effect
       * for hostname mismatches. */
      return interactive_check_cert (cert, pos, len, ssl, 0);
    }
    dprint (2, (debugfile, "ssl_verify_callback: hostname check passed\n"));
  }

  if (!preverify_ok || skip_mode)
  {
    /* automatic check from user's database */
    if (SslCertFile && check_certificate_by_digest (cert))
    {
      dprint (2, (debugfile, "ssl_verify_callback: digest check passed\n"));
      SSL_set_ex_data (ssl, SkipModeExDataIndex, NULL);
      return 1;
    }

#ifdef DEBUG
    /* log verification error */
    {
      int err = X509_STORE_CTX_get_error (ctx);
      snprintf (buf, sizeof (buf), "%s (%d)",
         X509_verify_cert_error_string (err), err);
      dprint (2, (debugfile, "X509_verify_cert: %s\n", buf));
    }
#endif

   /* prompt user */
    return interactive_check_cert (cert, pos, len, ssl, 1);
  }

  return 1;
}