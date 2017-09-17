ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, rnew,
                            "Symbolic link not allowed: %s", rnew->filename);