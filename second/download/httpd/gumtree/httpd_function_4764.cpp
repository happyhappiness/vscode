int ssl_callback_SSLVerify(int ok, X509_STORE_CTX *ctx)
{
    /* Get Apache context back through OpenSSL context */
    SSL *ssl = X509_STORE_CTX_get_ex_data(ctx,
                                          SSL_get_ex_data_X509_STORE_CTX_idx());
    conn_rec *conn      = (conn_rec *)SSL_get_app_data(ssl);
    request_rec *r      = (request_rec *)SSL_get_app_data2(ssl);
    server_rec *s       = r ? r->server : mySrvFromConn(conn);

    SSLSrvConfigRec *sc = mySrvConfig(s);
    SSLDirConfigRec *dc = r ? myDirConfig(r) : NULL;
    SSLConnRec *sslconn = myConnConfig(conn);
    modssl_ctx_t *mctx  = myCtxConfig(sslconn, sc);

    /* Get verify ingredients */
    int errnum   = X509_STORE_CTX_get_error(ctx);
    int errdepth = X509_STORE_CTX_get_error_depth(ctx);
    int depth, verify;

    /*
     * Log verification information
     */
    ssl_log_cxerror(SSLLOG_MARK, APLOG_DEBUG, 0, conn,
                    X509_STORE_CTX_get_current_cert(ctx),
                    "Certificate Verification, depth %d",
                    errdepth);

    /*
     * Check for optionally acceptable non-verifiable issuer situation
     */
    if (dc && (dc->nVerifyClient != SSL_CVERIFY_UNSET)) {
        verify = dc->nVerifyClient;
    }
    else {
        verify = mctx->auth.verify_mode;
    }

    if (verify == SSL_CVERIFY_NONE) {
        /*
         * SSLProxyVerify is either not configured or set to "none".
         * (this callback doesn't happen in the server context if SSLVerify
         *  is not configured or set to "none")
         */
        return TRUE;
    }

    if (ssl_verify_error_is_optional(errnum) &&
        (verify == SSL_CVERIFY_OPTIONAL_NO_CA))
    {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, conn,
                      "Certificate Verification: Verifiable Issuer is "
                      "configured as optional, therefore we're accepting "
                      "the certificate");

        sslconn->verify_info = "GENEROUS";
        ok = TRUE;
    }

    /*
     * Perform OCSP/CRL-based revocation checks
     */
    if (ok) {
        if (!(ok = ssl_callback_SSLVerify_CRL(ok, ctx, conn))) {
            errnum = X509_STORE_CTX_get_error(ctx);
        }
        
#ifdef HAVE_OCSP
        /* If there was an optional verification error, it's not
         * possible to perform OCSP validation since the issuer may be
         * missing/untrusted.  Fail in that case. */
        if (ok && ssl_verify_error_is_optional(errnum)
            && sc->server->ocsp_enabled) {
            X509_STORE_CTX_set_error(ctx, X509_V_ERR_APPLICATION_VERIFICATION);
            errnum = X509_V_ERR_APPLICATION_VERIFICATION;
            ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, conn,
                          "cannot perform OCSP validation for cert "
                          "if issuer has not been verified "
                          "(optional_no_ca configured)");
            ok = FALSE;
        }

        if (ok && sc->server->ocsp_enabled) {
            ok = modssl_verify_ocsp(ctx, sc, s, conn, conn->pool);
            if (!ok) {
                errnum = X509_STORE_CTX_get_error(ctx);
            }
        }
#endif
    }

    /*
     * If we already know it's not ok, log the real reason
     */
    if (!ok) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, conn,
                      "Certificate Verification: Error (%d): %s",
                      errnum, X509_verify_cert_error_string(errnum));

        if (sslconn->client_cert) {
            X509_free(sslconn->client_cert);
            sslconn->client_cert = NULL;
        }
        sslconn->client_dn = NULL;
        sslconn->verify_error = X509_verify_cert_error_string(errnum);
    }

    /*
     * Finally check the depth of the certificate verification
     */
    if (dc && (dc->nVerifyDepth != UNSET)) {
        depth = dc->nVerifyDepth;
    }
    else {
        depth = mctx->auth.verify_depth;
    }

    if (errdepth > depth) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, conn,
                      "Certificate Verification: Certificate Chain too long "
                      "(chain has %d certificates, but maximum allowed are "
                      "only %d)",
                      errdepth, depth);

        errnum = X509_V_ERR_CERT_CHAIN_TOO_LONG;
        sslconn->verify_error = X509_verify_cert_error_string(errnum);

        ok = FALSE;
    }

    /*
     * And finally signal OpenSSL the (perhaps changed) state
     */
    return ok;
}