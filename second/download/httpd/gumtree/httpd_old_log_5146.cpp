ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "StartThreads of %d not allowed, increasing to 1",
                         ap_threads_to_start);