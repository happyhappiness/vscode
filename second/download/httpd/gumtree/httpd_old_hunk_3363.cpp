
    /* ap_threads_to_start > ap_threads_limit effectively checked in
     * call to startup_workers(ap_threads_to_start) in ap_mpm_run()
     */
    if (ap_threads_to_start < 0) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: StartThreads of %d not allowed, "
                         "increasing to 1.", ap_threads_to_start);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "StartThreads of %d not allowed, increasing to 1",
                         ap_threads_to_start);
        }
        ap_threads_to_start = 1;
    }

    if (ap_threads_min_free < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MinSpareThreads of %d not allowed, "
                         "increasing to 1", ap_threads_min_free);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " to avoid almost certain server failure.");
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " Please read the documentation.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MinSpareThreads of %d not allowed, increasing to 1",
                         ap_threads_min_free);
        }
        ap_threads_min_free = 1;
    }

