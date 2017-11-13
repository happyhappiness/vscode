ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MinSpareServers of %d not allowed, increasing to 1",
                         ap_daemons_min_free);