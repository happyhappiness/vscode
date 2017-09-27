    }

    if (ap_daemons_limit > server_limit) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00318)
                         "WARNING: MaxRequestWorkers of %d would require %d "
                         "servers and ", max_workers, ap_daemons_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " would exceed ServerLimit of %d, decreasing to %d.",
                         server_limit, server_limit * threads_per_child);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " To increase, please see the ServerLimit "
                         "directive.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00319)
                         "MaxRequestWorkers of %d would require %d servers and "
                         "exceed ServerLimit of %d, decreasing to %d",
                         max_workers, ap_daemons_limit, server_limit,
                         server_limit * threads_per_child);
