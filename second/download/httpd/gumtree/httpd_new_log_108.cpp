ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                    "Symbolic link not allowed: %s", r->filename);