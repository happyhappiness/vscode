ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                     "WARNING: StartThreads of %d exceeds ThreadLimit value"
                     " of %d threads,", threads_to_start,
                     thread_limit);