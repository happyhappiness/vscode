ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00444)
                         "WARNING: ThreadsPerChild of %d exceeds ThreadLimit "
                         "of %d threads, decreasing to %d. To increase, please "
                         "see the ThreadLimit directive.",
                         ap_threads_per_child, thread_limit, thread_limit);