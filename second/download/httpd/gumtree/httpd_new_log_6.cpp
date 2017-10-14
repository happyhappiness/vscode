ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "Could not create a cache lock directory: %s",
                     path);