ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);