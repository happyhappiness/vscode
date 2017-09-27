        max_workers = tmp_max_workers;
    }

    if (ap_daemons_limit > server_limit) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00515)
                         "WARNING: MaxRequestWorkers of %d would require %d servers "
                         "and would exceed ServerLimit of %d, decreasing to %d. "
                         "To increase, please see the ServerLimit directive.",
                         max_workers, ap_daemons_limit, server_limit,
                         server_limit * threads_per_child);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00516)
                         "MaxRequestWorkers of %d would require %d servers and "
                         "exceed ServerLimit of %d, decreasing to %d",
                         max_workers, ap_daemons_limit, server_limit,
                         server_limit * threads_per_child);
