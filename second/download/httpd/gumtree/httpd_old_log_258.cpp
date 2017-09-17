ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);