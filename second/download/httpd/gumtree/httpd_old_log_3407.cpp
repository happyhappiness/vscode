ap_log_error(APLOG_MARK, APLOG_ERR, APR_EEXIST, r->server,
                     "Could not stat a cache lock file: %s",
                     lockname);