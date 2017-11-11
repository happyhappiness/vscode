static int event_check_config(apr_pool_t *p, apr_pool_t *plog,
                              apr_pool_t *ptemp, server_rec *s)
{
    int startup = 0;

    /* the reverse of pre_config, we want this only the first time around */
    if (retained->module_loads == 1) {
        startup = 1;
    }

    if (server_limit > MAX_SERVER_LIMIT) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00497)
                         "WARNING: ServerLimit of %d exceeds compile-time "
                         "limit of", server_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d servers, decreasing to %d.",
                         MAX_SERVER_LIMIT, MAX_SERVER_LIMIT);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00498)
                         "ServerLimit of %d exceeds compile-time limit "
                         "of %d, decreasing to match",
                         server_limit, MAX_SERVER_LIMIT);
        }
        server_limit = MAX_SERVER_LIMIT;
    }
    else if (server_limit < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00499)
                         "WARNING: ServerLimit of %d not allowed, "
                         "increasing to 1.", server_limit);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00500)
                         "ServerLimit of %d not allowed, increasing to 1",
                         server_limit);
        }
        server_limit = 1;
    }

    /* you cannot change ServerLimit across a restart; ignore
     * any such attempts
     */
    if (!retained->first_server_limit) {
        retained->first_server_limit = server_limit;
    }
    else if (server_limit != retained->first_server_limit) {
        /* don't need a startup console version here */
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00501)
                     "changing ServerLimit to %d from original value of %d "
                     "not allowed during restart",
                     server_limit, retained->first_server_limit);
        server_limit = retained->first_server_limit;
    }

    if (thread_limit > MAX_THREAD_LIMIT) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00502)
                         "WARNING: ThreadLimit of %d exceeds compile-time "
                         "limit of", thread_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d threads, decreasing to %d.",
                         MAX_THREAD_LIMIT, MAX_THREAD_LIMIT);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00503)
                         "ThreadLimit of %d exceeds compile-time limit "
                         "of %d, decreasing to match",
                         thread_limit, MAX_THREAD_LIMIT);
        }
        thread_limit = MAX_THREAD_LIMIT;
    }
    else if (thread_limit < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00504)
                         "WARNING: ThreadLimit of %d not allowed, "
                         "increasing to 1.", thread_limit);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00505)
                         "ThreadLimit of %d not allowed, increasing to 1",
                         thread_limit);
        }
        thread_limit = 1;
    }

    /* you cannot change ThreadLimit across a restart; ignore
     * any such attempts
     */
    if (!retained->first_thread_limit) {
        retained->first_thread_limit = thread_limit;
    }
    else if (thread_limit != retained->first_thread_limit) {
        /* don't need a startup console version here */
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00506)
                     "changing ThreadLimit to %d from original value of %d "
                     "not allowed during restart",
                     thread_limit, retained->first_thread_limit);
        thread_limit = retained->first_thread_limit;
    }

    if (threads_per_child > thread_limit) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00507)
                         "WARNING: ThreadsPerChild of %d exceeds ThreadLimit "
                         "of", threads_per_child);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d threads, decreasing to %d.",
                         thread_limit, thread_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " To increase, please see the ThreadLimit "
                         "directive.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00508)
                         "ThreadsPerChild of %d exceeds ThreadLimit "
                         "of %d, decreasing to match",
                         threads_per_child, thread_limit);
        }
        threads_per_child = thread_limit;
    }
    else if (threads_per_child < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00509)
                         "WARNING: ThreadsPerChild of %d not allowed, "
                         "increasing to 1.", threads_per_child);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00510)
                         "ThreadsPerChild of %d not allowed, increasing to 1",
                         threads_per_child);
        }
        threads_per_child = 1;
    }

    if (max_workers < threads_per_child) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00511)
                         "WARNING: MaxRequestWorkers of %d is less than "
                         "ThreadsPerChild of", max_workers);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d, increasing to %d.  MaxRequestWorkers must be at "
                         "least as large",
                         threads_per_child, threads_per_child);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " as the number of threads in a single server.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00512)
                         "MaxRequestWorkers of %d is less than ThreadsPerChild "
                         "of %d, increasing to match",
                         max_workers, threads_per_child);
        }
        max_workers = threads_per_child;
    }

    ap_daemons_limit = max_workers / threads_per_child;

    if (max_workers % threads_per_child) {
        int tmp_max_workers = ap_daemons_limit * threads_per_child;

        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00513)
                         "WARNING: MaxRequestWorkers of %d is not an integer "
                         "multiple of", max_workers);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " ThreadsPerChild of %d, decreasing to nearest "
                         "multiple %d,", threads_per_child,
                         tmp_max_workers);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " for a maximum of %d servers.",
                         ap_daemons_limit);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00514)
                         "MaxRequestWorkers of %d is not an integer multiple "
                         "of ThreadsPerChild of %d, decreasing to nearest "
                         "multiple %d", max_workers, threads_per_child,
                         tmp_max_workers);
        }
        max_workers = tmp_max_workers;
    }

    if (ap_daemons_limit > server_limit) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00515)
                         "WARNING: MaxRequestWorkers of %d would require %d "
                         "servers and ", max_workers, ap_daemons_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " would exceed ServerLimit of %d, decreasing to %d.",
                         server_limit, server_limit * threads_per_child);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " To increase, please see the ServerLimit "
                         "directive.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00516)
                         "MaxRequestWorkers of %d would require %d servers and "
                         "exceed ServerLimit of %d, decreasing to %d",
                         max_workers, ap_daemons_limit, server_limit,
                         server_limit * threads_per_child);
        }
        ap_daemons_limit = server_limit;
    }

    /* ap_daemons_to_start > ap_daemons_limit checked in ap_mpm_run() */
    if (ap_daemons_to_start < 0) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00517)
                         "WARNING: StartServers of %d not allowed, "
                         "increasing to 1.", ap_daemons_to_start);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00518)
                         "StartServers of %d not allowed, increasing to 1",
                         ap_daemons_to_start);
        }
        ap_daemons_to_start = 1;
    }

    if (min_spare_threads < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00519)
                         "WARNING: MinSpareThreads of %d not allowed, "
                         "increasing to 1", min_spare_threads);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " to avoid almost certain server failure.");
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " Please read the documentation.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00520)
                         "MinSpareThreads of %d not allowed, increasing to 1",
                         min_spare_threads);
        }
        min_spare_threads = 1;
    }

    /* max_spare_threads < min_spare_threads + threads_per_child
     * checked in ap_mpm_run()
     */

    return OK;
}