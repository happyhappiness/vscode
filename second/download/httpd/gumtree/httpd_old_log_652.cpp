ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                       "endif directive does not take tags in %s", r->filename);