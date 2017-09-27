                         "of %d, increasing to match",
                         max_workers, threads_per_child);
        }
        max_workers = threads_per_child;
    }

    active_daemons_limit = max_workers / threads_per_child;

    if (max_workers % threads_per_child) {
        int tmp_max_workers = active_daemons_limit * threads_per_child;

        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00513)
                         "WARNING: MaxRequestWorkers of %d is not an integer "
                         "multiple of ThreadsPerChild of %d, decreasing to nearest "
                         "multiple %d, for a maximum of %d servers.",
                         max_workers, threads_per_child, tmp_max_workers,
                         active_daemons_limit);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00514)
                         "MaxRequestWorkers of %d is not an integer multiple "
                         "of ThreadsPerChild of %d, decreasing to nearest "
                         "multiple %d", max_workers, threads_per_child,
                         tmp_max_workers);
        }
        max_workers = tmp_max_workers;
    }

    if (active_daemons_limit > server_limit) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00515)
                         "WARNING: MaxRequestWorkers of %d would require %d servers "
                         "and would exceed ServerLimit of %d, decreasing to %d. "
                         "To increase, please see the ServerLimit directive.",
                         max_workers, active_daemons_limit, server_limit,
                         server_limit * threads_per_child);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00516)
                         "MaxRequestWorkers of %d would require %d servers and "
                         "exceed ServerLimit of %d, decreasing to %d",
                         max_workers, active_daemons_limit, server_limit,
                         server_limit * threads_per_child);
        }
        active_daemons_limit = server_limit;
    }

    /* ap_daemons_to_start > active_daemons_limit checked in ap_mpm_run() */
    if (ap_daemons_to_start < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00517)
                         "WARNING: StartServers of %d not allowed, "
                         "increasing to 1.", ap_daemons_to_start);
        } else {
