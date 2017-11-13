ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, conn,
                          "cannot perform OCSP validation for cert "
                          "if issuer has not been verified "
                          "(optional_no_ca configured)");