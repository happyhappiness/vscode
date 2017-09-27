    }

    if (ap_min_spare_threads < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00215)
                         "WARNING: MinSpareThreads of %d not allowed, "
                         "increasing to 1 to avoid almost certain server failure. "
                         "Please read the documentation.", ap_min_spare_threads);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00216)
                         "MinSpareThreads of %d not allowed, increasing to 1",
                         ap_min_spare_threads);
        }
        ap_min_spare_threads = 1;
