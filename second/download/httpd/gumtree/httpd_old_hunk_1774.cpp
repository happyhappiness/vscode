
        sslconn->verify_info = "GENEROUS";
        ok = TRUE;
    }

    /*
     * Additionally perform CRL-based revocation checks
     */
    if (ok) {
        if (!(ok = ssl_callback_SSLVerify_CRL(ok, ctx, conn))) {
            errnum = X509_STORE_CTX_get_error(ctx);
        }
    }

    /*
     * If we already know it's not ok, log the real reason
     */
    if (!ok) {
