    if (max_workers % threads_per_child) {
        int tmp_max_workers = ap_daemons_limit * threads_per_child;

        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00316)
                         "WARNING: MaxRequestWorkers of %d is not an integer "
                         "multiple of ThreadsPerChild of %d, decreasing to nearest "
                         "multiple %d, for a maximum of %d servers.",
                         max_workers, threads_per_child, tmp_max_workers,
                         ap_daemons_limit);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00317)
                         "MaxRequestWorkers of %d is not an integer multiple of "
                         "ThreadsPerChild of %d, decreasing to nearest "
                         "multiple %d", max_workers, threads_per_child,
