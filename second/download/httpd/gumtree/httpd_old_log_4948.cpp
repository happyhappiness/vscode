ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Attempt to serve directory: %s", r->filename);