ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                    "%s: %s %ld/%d bytes %s BIO#%pp [mem: %pp] %s",
                    SSL_LIBRARY_NAME,
                    (cmd == (BIO_CB_WRITE|BIO_CB_RETURN) ? "write" : "read"),
                    rc, argi, (cmd == (BIO_CB_WRITE|BIO_CB_RETURN) ? "to" : "from"),
                    bio, argp,
                    (argp != NULL ? "(BIO dump follows)" : "(Oops, no memory buffer?)"));