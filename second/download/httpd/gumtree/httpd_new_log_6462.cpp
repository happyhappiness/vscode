ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00314)
                         "WARNING: MaxRequestWorkers of %d is less than "
                         "ThreadsPerChild of %d, increasing to %d. "
                         "MaxRequestWorkers must be at least as large "
                         "as the number of threads in a single server.",
                         max_workers, threads_per_child, threads_per_child);