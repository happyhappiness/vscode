ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "ThreadsPerChild of %d exceeds ThreadLimit "
                         "of %d, decreasing to match",
                         ap_threads_per_child, thread_limit);