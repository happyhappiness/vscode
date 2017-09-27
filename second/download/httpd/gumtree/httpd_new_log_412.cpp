ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "cache_disk: URL %s had a on-disk version mismatch",
                     r->uri);