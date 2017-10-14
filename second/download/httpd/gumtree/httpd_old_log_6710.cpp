ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00515)
                         "WARNING: MaxRequestWorkers of %d would require %d servers "
                         "and would exceed ServerLimit of %d, decreasing to %d. "
                         "To increase, please see the ServerLimit directive.",
                         max_workers, ap_daemons_limit, server_limit,
                         server_limit * threads_per_child);