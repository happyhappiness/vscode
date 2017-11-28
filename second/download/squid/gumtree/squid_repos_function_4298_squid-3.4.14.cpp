static void
ssl_free_SslErrors(void *, void *ptr, CRYPTO_EX_DATA *,
                   int, long, void *)
{
    Ssl::CertErrors *errs = static_cast <Ssl::CertErrors*>(ptr);
    delete errs;
}