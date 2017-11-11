int SSL_CTX_use_certificate_chain(
    SSL_CTX *ctx, char *file, int skipfirst, modssl_read_bio_cb_fn *cb)
{
    BIO *bio;
    X509 *x509;
    unsigned long err;
    int n;
    STACK_OF(X509) *extra_certs;

    if ((bio = BIO_new(BIO_s_file_internal())) == NULL)
        return -1;
    if (BIO_read_filename(bio, file) <= 0) {
        BIO_free(bio);
        return -1;
    }
    /* optionally skip a leading server certificate */
    if (skipfirst) {
        if ((x509 = modssl_PEM_read_bio_X509(bio, NULL, cb, NULL)) == NULL) {
            BIO_free(bio);
            return -1;
        }
        X509_free(x509);
    }
    /* free a perhaps already configured extra chain */
    extra_certs=SSL_CTX_get_extra_certs(ctx);
    if (extra_certs != NULL) {
        sk_X509_pop_free((STACK_OF(X509) *)extra_certs, X509_free);
        SSL_CTX_set_extra_certs(ctx,NULL);
    }
    /* create new extra chain by loading the certs */
    n = 0;
    while ((x509 = modssl_PEM_read_bio_X509(bio, NULL, cb, NULL)) != NULL) {
        if (!SSL_CTX_add_extra_chain_cert(ctx, x509)) {
            X509_free(x509);
            BIO_free(bio);
            return -1;
        }
        n++;
    }
    /* Make sure that only the error is just an EOF */
    if ((err = ERR_peek_error()) > 0) {
        if (!(   ERR_GET_LIB(err) == ERR_LIB_PEM
              && ERR_GET_REASON(err) == PEM_R_NO_START_LINE)) {
            BIO_free(bio);
            return -1;
        }
        while (ERR_get_error() > 0) ;
    }
    BIO_free(bio);
    return n;
}