ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                            "Init: Unable to read server private key from "
                            "file %s [Hint: Perhaps it is in a separate file? "
                            "  See SSLCertificateKeyFile]", szPath);