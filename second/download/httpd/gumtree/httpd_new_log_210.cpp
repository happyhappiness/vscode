ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "exec used but not allowed in %s", r->filename);