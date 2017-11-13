ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
         "client submitted cookie '%s' more than once: %s", v.name, r->uri);