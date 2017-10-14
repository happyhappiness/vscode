ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Certificate Verification: Error (%d): %s",
                     errnum, X509_verify_cert_error_string(errnum));