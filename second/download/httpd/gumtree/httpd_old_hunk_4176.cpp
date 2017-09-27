    }

    if (ap_daemons_min_free < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00186)
                         "WARNING: MinSpareServers of %d not allowed, "
                         "increasing to 1", ap_daemons_min_free);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " to avoid almost certain server failure.");
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " Please read the documentation.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00187)
                         "MinSpareServers of %d not allowed, increasing to 1",
                         ap_daemons_min_free);
        }
        ap_daemons_min_free = 1;
