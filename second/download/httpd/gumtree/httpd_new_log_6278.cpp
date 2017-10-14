ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00228)
                         "WARNING: MaxThreads of %d exceeds compile-time "
                         "limit of %d threads, decreasing to %d. "
                         "To increase, please see the HARD_THREAD_LIMIT "
                         "define in server/mpm/netware%s.",
                         ap_threads_limit, HARD_THREAD_LIMIT, HARD_THREAD_LIMIT,
                         MPM_HARD_LIMITS_FILE);