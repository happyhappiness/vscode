ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MaxThreads of %d exceeds compile-time "
                         "limit of", ap_threads_limit);