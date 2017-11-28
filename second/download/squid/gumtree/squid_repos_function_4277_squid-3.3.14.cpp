static void
ssl_free_SslErrors(void *, void *ptr, CRYPTO_EX_DATA *,
                   int, long, void *)
{
    Ssl::Errors *errs = static_cast <Ssl::Errors*>(ptr);
    delete errs;
}