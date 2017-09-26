ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Symbolic link not allowed: %s",
                                  r->filename);