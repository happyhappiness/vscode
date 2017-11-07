static int ssl_cache_trusted_cert (X509 *c)
{
  dprint (1, (debugfile, "trusted: %s\n", c->name));
  if (!SslSessionCerts)
    SslSessionCerts = sk_X509_new_null();
  return (sk_X509_push (SslSessionCerts, X509_dup(c)));
}