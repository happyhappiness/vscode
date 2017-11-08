static char *ssl_var_lookup_ssl_cert_valid(apr_pool_t *p, ASN1_TIME *tm)
{
    char *result;
    BIO* bio;
    int n;

    if ((bio = BIO_new(BIO_s_mem())) == NULL)
        return NULL;
    ASN1_TIME_print(bio, tm);
    n = BIO_pending(bio);
    result = apr_pcalloc(p, n+1);
    n = BIO_read(bio, result, n);
    result[n] = NUL;
    BIO_free(bio);
    return result;
}