static int winnt_check_config(apr_pool_t *pconf, apr_pool_t *plog,
                              apr_pool_t *ptemp, server_rec* s)
{
    int is_parent;
    int startup = 0;

    /* We want this only in the parent and only the first time around */
    is_parent = (parent_pid == my_pid);
    if (is_parent &&
        ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG) {
        startup = 1;
    }

    if (thread_limit > MAX_THREAD_LIMIT) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00439)
                         "WARNING: ThreadLimit of %d exceeds compile-time "
                         "limit of", thread_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d threads, decreasing to %d.",
                         MAX_THREAD_LIMIT, MAX_THREAD_LIMIT);
        } else if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00440)
                         "ThreadLimit of %d exceeds compile-time limit "
                         "of %d, decreasing to match",
                         thread_limit, MAX_THREAD_LIMIT);
        }
        thread_limit = MAX_THREAD_LIMIT;
    }
    else if (thread_limit < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00441)
                         "WARNING: ThreadLimit of %d not allowed, "
                         "increasing to 1.", thread_limit);
        } else if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00442)
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
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00443)
                         "changing ThreadLimit to %d from original value "
                         "of %d not allowed during restart",
                         thread_limit, first_thread_limit);
        }
        thread_limit = first_thread_limit;
    }

    if (ap_threads_per_child > thread_limit) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00444)
                         "WARNING: ThreadsPerChild of %d exceeds ThreadLimit "
                         "of", ap_threads_per_child);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d threads, decreasing to %d.",
                         thread_limit, thread_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " To increase, please see the ThreadLimit "
                         "directive.");
        } else if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00445)
                         "ThreadsPerChild of %d exceeds ThreadLimit "
                         "of %d, decreasing to match",
                         ap_threads_per_child, thread_limit);
        }
        ap_threads_per_child = thread_limit;
    }
    else if (ap_threads_per_child < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00446)
                         "WARNING: ThreadsPerChild of %d not allowed, "
                         "increasing to 1.", ap_threads_per_child);
        } else if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00447)
                         "ThreadsPerChild of %d not allowed, increasing to 1",
                         ap_threads_per_child);
        }
        ap_threads_per_child = 1;
    }

    return OK;
}