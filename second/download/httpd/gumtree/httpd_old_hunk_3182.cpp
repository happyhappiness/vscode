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
