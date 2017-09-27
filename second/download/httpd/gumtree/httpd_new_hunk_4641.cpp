        /* starting with OpenSSL 1.0, X509_STORE_CTX_get_current_cert()
         * may yield NULL. Return early, but leave the ctx error as is. */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                      "No cert available to check with OCSP");
        return 1;
    }
    else if (X509_check_issued(cert,cert) == X509_V_OK) {
        /* don't do OCSP checking for valid self-issued certs */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                      "Skipping OCSP check for valid self-issued cert");
        X509_STORE_CTX_set_error(ctx, X509_V_OK);
        return 1;
    }
