ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "DBM user %s not found: %s", r->user, r->filename);