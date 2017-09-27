    if (is_parent && restart_num++ == 0) {
        startup = 1;
    }

    if (thread_limit > MAX_THREAD_LIMIT) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: ThreadLimit of %d exceeds compile-time "
                         "limit of", thread_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d threads, decreasing to %d.",
                         MAX_THREAD_LIMIT, MAX_THREAD_LIMIT);
        } else if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "ThreadLimit of %d exceeds compile-time limit "
                         "of %d, decreasing to match",
                         thread_limit, MAX_THREAD_LIMIT);
        }
        thread_limit = MAX_THREAD_LIMIT;
    }
    else if (thread_limit < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: ThreadLimit of %d not allowed, "
                         "increasing to 1.", thread_limit);
        } else if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "ThreadLimit of %d not allowed, increasing to 1",
                         thread_limit);
        }
        thread_limit = 1;
    }

