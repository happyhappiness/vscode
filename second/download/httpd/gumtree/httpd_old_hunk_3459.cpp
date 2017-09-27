     */
    if (!retained->first_thread_limit) {
        retained->first_thread_limit = thread_limit;
    }
    else if (thread_limit != retained->first_thread_limit) {
        /* don't need a startup console version here */
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "changing ThreadLimit to %d from original value of %d "
                     "not allowed during restart",
                     thread_limit, retained->first_thread_limit);
        thread_limit = retained->first_thread_limit;
    }

    if (threads_per_child > thread_limit) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: ThreadsPerChild of %d exceeds ThreadLimit "
                         "of", threads_per_child);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d threads, decreasing to %d.",
                         thread_limit, thread_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " To increase, please see the ThreadLimit "
                         "directive.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "ThreadsPerChild of %d exceeds ThreadLimit "
                         "of %d, decreasing to match",
                         threads_per_child, thread_limit);
        }
        threads_per_child = thread_limit;
    }
    else if (threads_per_child < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: ThreadsPerChild of %d not allowed, "
                         "increasing to 1.", threads_per_child);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "ThreadsPerChild of %d not allowed, increasing to 1",
                         threads_per_child);
        }
        threads_per_child = 1;
    }

    if (max_clients < threads_per_child) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MaxClients of %d is less than "
                         "ThreadsPerChild of", max_clients);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d, increasing to %d.  MaxClients must be at "
                         "least as large",
                         threads_per_child, threads_per_child);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " as the number of threads in a single server.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MaxClients of %d is less than ThreadsPerChild "
                         "of %d, increasing to match",
                         max_clients, threads_per_child);
        }
        max_clients = threads_per_child;
    }

    ap_daemons_limit = max_clients / threads_per_child;

    if (max_clients % threads_per_child) {
        int tmp_max_clients = ap_daemons_limit * threads_per_child;

        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MaxClients of %d is not an integer "
                         "multiple of", max_clients);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " ThreadsPerChild of %d, decreasing to nearest "
                         "multiple %d,", threads_per_child,
                         tmp_max_clients);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " for a maximum of %d servers.",
                         ap_daemons_limit);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MaxClients of %d is not an integer multiple of "
                         "ThreadsPerChild of %d, decreasing to nearest "
                         "multiple %d", max_clients, threads_per_child,
                         tmp_max_clients);
        }
        max_clients = tmp_max_clients;
    }

    if (ap_daemons_limit > server_limit) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MaxClients of %d would require %d "
                         "servers and ", max_clients, ap_daemons_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " would exceed ServerLimit of %d, decreasing to %d.",
                         server_limit, server_limit * threads_per_child);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " To increase, please see the ServerLimit "
                         "directive.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MaxClients of %d would require %d servers and "
                         "exceed ServerLimit of %d, decreasing to %d",
                         max_clients, ap_daemons_limit, server_limit,
                         server_limit * threads_per_child);
        }
        ap_daemons_limit = server_limit;
    }

    /* ap_daemons_to_start > ap_daemons_limit checked in worker_run() */
    if (ap_daemons_to_start < 0) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: StartServers of %d not allowed, "
                         "increasing to 1.", ap_daemons_to_start);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "StartServers of %d not allowed, increasing to 1",
                         ap_daemons_to_start);
        }
        ap_daemons_to_start = 1;
    }

    if (min_spare_threads < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MinSpareThreads of %d not allowed, "
                         "increasing to 1", min_spare_threads);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " to avoid almost certain server failure.");
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " Please read the documentation.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MinSpareThreads of %d not allowed, increasing to 1",
                         min_spare_threads);
        }
        min_spare_threads = 1;
    }

