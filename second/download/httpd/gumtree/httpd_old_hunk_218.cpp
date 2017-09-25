     */
    if (!ok) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Certificate Verification: Error (%d): %s",
                     errnum, X509_verify_cert_error_string(errnum));

        sslconn->client_dn = NULL;
        sslconn->client_cert = NULL;
        sslconn->verify_error = X509_verify_cert_error_string(errnum);
    }

    /*
     * Finally check the depth of the certificate verification
     */
