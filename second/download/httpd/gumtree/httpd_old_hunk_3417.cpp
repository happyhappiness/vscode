    if (!first_thread_limit) {
        first_thread_limit = thread_limit;
    }
    else if (thread_limit != first_thread_limit) {
        /* Don't need a startup console version here */
        if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "changing ThreadLimit to %d from original value "
                         "of %d not allowed during restart",
                         thread_limit, first_thread_limit);
        }
        thread_limit = first_thread_limit;
    }

    if (ap_threads_per_child > thread_limit) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: ThreadsPerChild of %d exceeds ThreadLimit "
                         "of", ap_threads_per_child);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d threads, decreasing to %d.",
                         thread_limit, thread_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " To increase, please see the ThreadLimit "
                         "directive.");
        } else if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "ThreadsPerChild of %d exceeds ThreadLimit "
                         "of %d, decreasing to match",
                         ap_threads_per_child, thread_limit);
        }
        ap_threads_per_child = thread_limit;
    }
    else if (ap_threads_per_child < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: ThreadsPerChild of %d not allowed, "
                         "increasing to 1.", ap_threads_per_child);
        } else if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "ThreadsPerChild of %d not allowed, increasing to 1",
                         ap_threads_per_child);
        }
        ap_threads_per_child = 1;
    }

