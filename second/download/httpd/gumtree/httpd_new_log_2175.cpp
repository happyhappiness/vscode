ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MaxThreads of %d exceeds compile-time limit "
                         "of %d, decreasing to match",
                         ap_threads_limit, HARD_THREAD_LIMIT);