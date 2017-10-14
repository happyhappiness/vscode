ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: StartThreads of %d not allowed, "
                         "increasing to 1.", ap_threads_to_start);