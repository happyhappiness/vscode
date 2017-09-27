    }

    if (ap_threads_min_free < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00233)
                         "WARNING: MinSpareThreads of %d not allowed, "
                         "increasing to 1 to avoid almost certain server failure. "
                         "Please read the documentation.", ap_threads_min_free);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00234)
                         "MinSpareThreads of %d not allowed, increasing to 1",
                         ap_threads_min_free);
        }
        ap_threads_min_free = 1;
