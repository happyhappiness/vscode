ssl_log_cxerror(SSLLOG_MARK, APLOG_DEBUG, 0, conn,
                    X509_STORE_CTX_get_current_cert(ctx),
                    "Certificate Verification, depth %d",
                    errdepth);