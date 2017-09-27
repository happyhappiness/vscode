    }

    if (min_spare_threads < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00322)
                         "WARNING: MinSpareThreads of %d not allowed, "
                         "increasing to 1 to avoid almost certain server failure. "
                         "Please read the documentation.", min_spare_threads);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00323)
                         "MinSpareThreads of %d not allowed, increasing to 1",
                         min_spare_threads);
        }
        min_spare_threads = 1;
