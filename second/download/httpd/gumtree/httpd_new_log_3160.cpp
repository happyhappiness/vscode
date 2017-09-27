ap_log_cserror(APLOG_MARK, APLOG_TRACE4, 0, c, s,
                    "%s: I/O error, %d bytes expected to %s on BIO#%pp [mem: %pp]",
                    SSL_LIBRARY_NAME, argi,
                    (cmd == (BIO_CB_WRITE|BIO_CB_RETURN) ? "write" : "read"),
                    bio, argp);