ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02247)
                            "Init: Unable to read server private key from "
                            "file %s [Hint: Perhaps it is in a separate file? "
                            "  See SSLCertificateKeyFile]", szPath);