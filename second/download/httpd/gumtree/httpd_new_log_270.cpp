ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                        "Unmatched '(' in \"%s\" in file %s",
                        expr, r->filename);