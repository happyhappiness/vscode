     * the "real" error, as returned by OpenSSL.
     */
    if (!ok && errnum == X509_V_ERR_CRL_HAS_EXPIRED) {
        X509_STORE_CTX_set_error(ctx, -1);
    }

    if (!ok && errnum == X509_V_ERR_UNABLE_TO_GET_CRL
            && (mctx->crl_check_mask & SSL_CRLCHECK_NO_CRL_FOR_CERT_OK)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, conn,
                      "Certificate Verification: Temporary error (%d): %s: "
                      "optional therefore we're accepting the certificate",
                      errnum, X509_verify_cert_error_string(errnum));
        X509_STORE_CTX_set_error(ctx, X509_V_OK);
        errnum = X509_V_OK;
        ok = TRUE;
    }

#ifndef OPENSSL_NO_OCSP
    /*
     * Perform OCSP-based revocation checks
     */
    if (ok && sc->server->ocsp_enabled) {
        /* If there was an optional verification error, it's not
