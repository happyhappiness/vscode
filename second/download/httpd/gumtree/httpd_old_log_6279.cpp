ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d threads, decreasing to %d.",
                         HARD_THREAD_LIMIT, HARD_THREAD_LIMIT);