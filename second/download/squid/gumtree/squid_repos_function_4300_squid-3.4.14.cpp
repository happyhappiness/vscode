static void
ssl_free_CertChain(void *, void *ptr, CRYPTO_EX_DATA *,
                   int, long, void *)
{
    STACK_OF(X509) *certsChain = static_cast <STACK_OF(X509) *>(ptr);
    sk_X509_pop_free(certsChain,X509_free);
}