ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                     "disk_cache: Could not store URL %s [%d]", key, rv);