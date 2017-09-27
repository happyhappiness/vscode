    if (restart_num++ == 0) {
        startup = 1;
    }

    if (ap_threads_limit > HARD_THREAD_LIMIT) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MaxThreads of %d exceeds compile-time "
                         "limit of", ap_threads_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d threads, decreasing to %d.",
                         HARD_THREAD_LIMIT, HARD_THREAD_LIMIT);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " To increase, please see the HARD_THREAD_LIMIT"
                         "define in");
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " server/mpm/netware%s.", MPM_HARD_LIMITS_FILE);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MaxThreads of %d exceeds compile-time limit "
                         "of %d, decreasing to match",
                         ap_threads_limit, HARD_THREAD_LIMIT);
        }
        ap_threads_limit = HARD_THREAD_LIMIT;
    }
    else if (ap_threads_limit < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MaxThreads of %d not allowed, "
                         "increasing to 1.", ap_threads_limit);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MaxThreads of %d not allowed, increasing to 1",
                         ap_threads_limit);
        }
