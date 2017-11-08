static char *ssl_var_lookup_ssl_cert_dn_oneline(apr_pool_t *p, request_rec *r,
                                                X509_NAME *xsname)
{
    char *result = NULL;
    SSLDirConfigRec *dc;
    int legacy_format = 0;
    if (r) {
        dc = myDirConfig(r);
        legacy_format = dc->nOptions & SSL_OPT_LEGACYDNFORMAT;
    }
    if (legacy_format) {
        char *cp = X509_NAME_oneline(xsname, NULL, 0);
        result = apr_pstrdup(p, cp);
        OPENSSL_free(cp);
    }
    else {
        BIO* bio;
        int n;
        unsigned long flags = XN_FLAG_RFC2253 & ~ASN1_STRFLGS_ESC_MSB;
        if ((bio = BIO_new(BIO_s_mem())) == NULL)
            return NULL;
        X509_NAME_print_ex(bio, xsname, 0, flags);
        n = BIO_pending(bio);
        if (n > 0) {
            result = apr_palloc(p, n+1);
            n = BIO_read(bio, result, n);
            result[n] = NUL;
        }
        BIO_free(bio);
    }
    return result;
}