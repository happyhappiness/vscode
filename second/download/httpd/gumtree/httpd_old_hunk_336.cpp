    }

    /*
     * If we already know it's not ok, log the real reason
     */
    if (!ok) {
        ssl_log(s, SSL_LOG_ERROR,
                "Certificate Verification: Error (%d): %s",
                errnum, X509_verify_cert_error_string(errnum));

        sslconn->client_dn = NULL;
        sslconn->client_cert = NULL;
        sslconn->verify_error = X509_verify_cert_error_string(errnum);
    }

