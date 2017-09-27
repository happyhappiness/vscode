ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, conn,
                      "Certificate Verification: Temporary error (%d): %s: "
                      "optional therefore we're accepting the certificate",
                      errnum, X509_verify_cert_error_string(errnum));