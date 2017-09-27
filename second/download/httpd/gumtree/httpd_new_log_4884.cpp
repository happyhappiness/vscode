ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, conn, APLOGNO(02039)
                          "Certificate Verification: Error (%d): %s",
                          errnum, X509_verify_cert_error_string(errnum));