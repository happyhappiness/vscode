ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00186)
                         "WARNING: MinSpareServers of %d not allowed, "
                         "increasing to 1 to avoid almost certain server failure. "
                         "Please read the documentation.", ap_daemons_min_free);