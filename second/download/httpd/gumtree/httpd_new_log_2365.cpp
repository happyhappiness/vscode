ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "ThreadLimit of %d not allowed, increasing to 1",
                         thread_limit);