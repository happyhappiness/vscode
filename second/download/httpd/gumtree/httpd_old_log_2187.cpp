ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                    "WARNING: MaxThreads of %d exceeds compile time limit "
                    "of %d threads,", ap_threads_limit, HARD_THREAD_LIMIT);