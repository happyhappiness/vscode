ap_log_error(APLOG_MARK, APLOG_INFO, status, r->server,
                     "Cache lock file for '%s' too old, removing: %s",
                     r->uri, lockname);