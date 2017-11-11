char *SSL_X509_NAME_to_string(apr_pool_t *p, X509_NAME *dn, unsigned int maxlen)
{
    char *result = NULL;
    BIO *bio;
    int len;

    if ((bio = BIO_new(BIO_s_mem())) == NULL)
        return NULL;
    X509_NAME_print_ex(bio, dn, 0, XN_FLAG_RFC2253);
    len = BIO_pending(bio);
    if (len > 0) {
        result = apr_palloc(p, maxlen ? maxlen+1 : len+1);
        if (maxlen && maxlen < len) {
            len = BIO_read(bio, result, maxlen);
            if (maxlen > 2) {
                /* insert trailing ellipsis if there's enough space */
                apr_snprintf(result + maxlen - 3, 4, "...");
            }
        } else {
            len = BIO_read(bio, result, len);
        }
        result[len] = NUL;
    }
    BIO_free(bio);

    return result;
}