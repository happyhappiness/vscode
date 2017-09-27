     * the "real" error, as returned by OpenSSL.
     */
    if (!ok && errnum == X509_V_ERR_CRL_HAS_EXPIRED) {
        X509_STORE_CTX_set_error(ctx, -1);
    }

#ifndef OPENSSL_NO_OCSP
    /*
     * Perform OCSP-based revocation checks
     */
    if (ok && sc->server->ocsp_enabled) {
        /* If there was an optional verification error, it's not
