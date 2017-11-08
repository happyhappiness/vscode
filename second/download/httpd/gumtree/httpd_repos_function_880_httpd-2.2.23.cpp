static char *ssl_var_lookup_ssl_cert_PEM(apr_pool_t *p, X509 *xs)
{
    char *result;
    BIO *bio;
    int n;

    if ((bio = BIO_new(BIO_s_mem())) == NULL)
        return NULL;
    PEM_write_bio_X509(bio, xs);
    n = BIO_pending(bio);
    result = apr_pcalloc(p, n+1);
    n = BIO_read(bio, result, n);
    result[n] = NUL;
    BIO_free(bio);
    return result;
}