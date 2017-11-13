ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "SSL proxy client cert chain verification failed for %s: %s",
                         cert_dn, X509_verify_cert_error_string(err));