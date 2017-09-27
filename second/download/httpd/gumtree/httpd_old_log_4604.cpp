ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
             "proxy: %s returned by %s", message, r->uri);