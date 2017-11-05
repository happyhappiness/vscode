int modssl_verify_ocsp(X509_STORE_CTX *ctx, SSLSrvConfigRec *sc,
                       server_rec *s, conn_rec *c, apr_pool_t *pool)
{
    X509 *cert = X509_STORE_CTX_get_current_cert(ctx);
    apr_pool_t *vpool;
    int rv;

    if (!cert) {
        /* starting with OpenSSL 1.0, X509_STORE_CTX_get_current_cert()
         * may yield NULL. Return early, but leave the ctx error as is. */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                      "No cert available to check with OCSP");
        return 1;
    }
    else if (cert->valid && X509_check_issued(cert,cert) == X509_V_OK) {
        /* don't do OCSP checking for valid self-issued certs */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                      "Skipping OCSP check for valid self-issued cert");
        X509_STORE_CTX_set_error(ctx, X509_V_OK);
        return 1;
    }

    /* Create a temporary pool to constrain memory use (the passed-in
     * pool may be e.g. a connection pool). */
    apr_pool_create(&vpool, pool);

    rv = verify_ocsp_status(cert, ctx, c, sc, s, vpool);

    apr_pool_destroy(vpool);

    /* Propagate the verification status back to the passed-in
     * context. */
    switch (rv) {
    case V_OCSP_CERTSTATUS_GOOD:
        X509_STORE_CTX_set_error(ctx, X509_V_OK);
        break;

    case V_OCSP_CERTSTATUS_REVOKED:
        X509_STORE_CTX_set_error(ctx, X509_V_ERR_CERT_REVOKED);
        break;

    case V_OCSP_CERTSTATUS_UNKNOWN:
        /* correct error code for application errors? */
        X509_STORE_CTX_set_error(ctx, X509_V_ERR_APPLICATION_VERIFICATION);
        break;
    }

    return rv == V_OCSP_CERTSTATUS_GOOD;
}