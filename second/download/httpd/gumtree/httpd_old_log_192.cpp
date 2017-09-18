ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                        "Unmatched '(' in \"%s\" in file %s",
                        expr, r->filename);