ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00508)
                         "ThreadsPerChild of %d exceeds ThreadLimit "
                         "of %d, decreasing to match",
                         threads_per_child, thread_limit);