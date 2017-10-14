ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "changing ThreadLimit to %d from original value of %d "
                     "not allowed during restart",
                     thread_limit, retained->first_thread_limit);