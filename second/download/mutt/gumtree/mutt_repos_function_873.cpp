static int ssl_check_preauth (X509 *cert, const char* host)
{
  char buf[SHORT_STRING];

  /* check session cache first */
  if (check_certificate_cache (cert))
  {
    dprint (2, (debugfile, "ssl_check_preauth: using cached certificate\n"));
    return 1;
  }

  buf[0] = 0;
  if (host && option (OPTSSLVERIFYHOST) != MUTT_NO)
  {
    if (!check_host (cert, host, buf, sizeof (buf)))
    {
      mutt_error (_("Certificate host check failed: %s"), buf);
      mutt_sleep (2);
      return -1;
    }
    dprint (2, (debugfile, "ssl_check_preauth: hostname check passed\n"));
  }

  if (check_certificate_by_signer (cert))
  {
    dprint (2, (debugfile, "ssl_check_preauth: signer check passed\n"));
    return 1;
  }

  /* automatic check from user's database */
  if (SslCertFile && check_certificate_by_digest (cert))
  {
    dprint (2, (debugfile, "ssl_check_preauth: digest check passed\n"));
    return 1;
  }

  return 0;
}