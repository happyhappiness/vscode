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
