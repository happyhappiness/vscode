static int ssl_cache_trusted_cert (X509 *c)
{
  dprint (1, (debugfile, "ssl_cache_trusted_cert: trusted\n"));
  if (!SslSessionCerts)
    SslSessionCerts = sk_X509_new_null();
  return (sk_X509_push (SslSessionCerts, X509_dup(c)));
}