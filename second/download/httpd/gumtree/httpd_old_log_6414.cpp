ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d, increasing to %d.  MaxRequestWorkers must be at "
                         "least as large",
                         threads_per_child, threads_per_child);