ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "threads, lowering ThreadsPerChild to %d. To increase, please"
                     " see the", thread_limit);