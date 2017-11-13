static int winnt_check_config(apr_pool_t *pconf, apr_pool_t *plog,
                              apr_pool_t *ptemp, server_rec* s)
{
    int is_parent;
    static int restart_num = 0;
    int startup = 0;

    /* We want this only in the parent and only the first time around */
    is_parent = (parent_pid == my_pid);
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

    /* You cannot change ThreadLimit across a restart; ignore
     * any such attempts.
     */
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

    return OK;
}