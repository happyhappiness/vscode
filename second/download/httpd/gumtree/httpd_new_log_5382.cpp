ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00306)
                         "ThreadLimit of %d exceeds compile-time limit "
                         "of %d, decreasing to match",
                         thread_limit, MAX_THREAD_LIMIT);