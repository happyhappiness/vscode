ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                     "disk_cache: Could not cache URL %s [%d]", key, rv);