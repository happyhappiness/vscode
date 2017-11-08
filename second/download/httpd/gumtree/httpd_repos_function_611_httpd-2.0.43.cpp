int SSL_CTX_use_certificate_chain(
    SSL_CTX *ctx, char *file, int skipfirst, int (*cb)(char*,int,int,void*))
{
    BIO *bio;
    X509 *x509;
    unsigned long err;
    int n;
    STACK *extra_certs;

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
#if SSL_LIBRARY_VERSION < 0x00904000
    while ((x509 = PEM_read_bio_X509(bio, NULL, cb)) != NULL) {
#else
    while ((x509 = PEM_read_bio_X509(bio, NULL, cb, NULL)) != NULL) {
#endif
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

/*  _________________________________________________________________
**
**  Session Stuff
**  _________________________________________________________________
*/

char *SSL_SESSION_id2sz(unsigned char *id, int idlen,
                        char *str, int strsize)
{
    char *cp;
    int n;

    cp = str;
    for (n = 0; n < idlen && n < SSL_MAX_SSL_SESSION_ID_LENGTH; n++) {
        apr_snprintf(cp, strsize - (cp-str), "%02X", id[n]);
        cp += 2;
    }
    *cp = NUL;
    return str;
}

/* sslc+OpenSSL compat */

int modssl_session_get_time(SSL_SESSION *session)
{
#ifdef OPENSSL_VERSION_NUMBER
    return SSL_SESSION_get_time(session);
#else /* assume sslc */
    CRYPTO_TIME_T ct;
    SSL_SESSION_get_time(session, &ct);
    return CRYPTO_time_to_int(&ct);
#endif
}

#ifndef SSLC_VERSION_NUMBER
#define SSLC_VERSION_NUMBER 0x0000
#endif

DH *modssl_dh_configure(unsigned char *p, int plen,
                        unsigned char *g, int glen)
{
    DH *dh;

    if (!(dh = DH_new())) {
        return NULL;
    }

#if defined(OPENSSL_VERSION_NUMBER) || (SSLC_VERSION_NUMBER < 0x2000)
    dh->p = BN_bin2bn(p, plen, NULL);
    dh->g = BN_bin2bn(g, glen, NULL);
    if (!(dh->p && dh->g)) {
        DH_free(dh);
        return NULL;
    }
#else
    R_EITEMS_add(dh->data, PK_TYPE_DH, PK_DH_P, 0, p, plen, R_EITEMS_PF_COPY);
    R_EITEMS_add(dh->data, PK_TYPE_DH, PK_DH_G, 0, g, glen, R_EITEMS_PF_COPY);
#endif

    return dh;
}