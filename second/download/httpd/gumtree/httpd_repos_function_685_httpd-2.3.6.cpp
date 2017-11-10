static void certinfo_free(void *parent, void *ptr, CRYPTO_EX_DATA *ad,
                                        int idx, long argl, void *argp)
{
    certinfo *cinf = ptr;

    if (!cinf)
        return;
    if (cinf->uri)
        OPENSSL_free(cinf->uri);
    OPENSSL_free(cinf);
}