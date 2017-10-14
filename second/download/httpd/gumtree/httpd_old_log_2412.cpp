ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                    "WARNING: ThreadLimit of %d exceeds compile time limit "
                    "of %d servers,", thread_limit, MAX_THREAD_LIMIT);