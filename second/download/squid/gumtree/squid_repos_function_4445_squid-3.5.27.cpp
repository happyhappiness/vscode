static void
ssl_free_X509(void *, void *ptr, CRYPTO_EX_DATA *,
              int, long, void *)
{
    X509  *cert = static_cast <X509 *>(ptr);
    X509_free(cert);
}