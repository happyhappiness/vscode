ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "Can't open directory for index: %s", r->filename);