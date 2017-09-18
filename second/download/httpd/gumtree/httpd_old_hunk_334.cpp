    int errdepth = X509_STORE_CTX_get_error_depth(ctx);
    int depth, verify;

    /*
     * Log verification information
     */
    if (sc->log_level >= SSL_LOG_TRACE) {
        X509 *cert  = X509_STORE_CTX_get_current_cert(ctx);
        char *sname = X509_NAME_oneline(X509_get_subject_name(cert), NULL, 0);
        char *iname = X509_NAME_oneline(X509_get_issuer_name(cert),  NULL, 0);

        ssl_log(s, SSL_LOG_TRACE,
                "Certificate Verification: depth: %d, subject: %s, issuer: %s",
                errdepth,
                sname ? sname : "-unknown-",
                iname ? iname : "-unknown-");

        if (sname) {
            free(sname);
        }

        if (iname) {
