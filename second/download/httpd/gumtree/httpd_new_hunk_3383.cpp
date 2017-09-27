     */
    if (!retained->first_server_limit) {
        retained->first_server_limit = server_limit;
    }
    else if (server_limit != retained->first_server_limit) {
        /* don't need a startup console version here */
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00179)
                     "changing ServerLimit to %d from original value of %d "
                     "not allowed during restart",
                     server_limit, retained->first_server_limit);
        server_limit = retained->first_server_limit;
    }

    if (ap_daemons_limit > server_limit) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00180)
                         "WARNING: MaxRequestWorkers of %d exceeds ServerLimit "
                         "value of", ap_daemons_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d servers, decreasing MaxRequestWorkers to %d.",
                         server_limit, server_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " To increase, please see the ServerLimit "
                         "directive.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00181)
                         "MaxRequestWorkers of %d exceeds ServerLimit value "
                         "of %d, decreasing to match",
                         ap_daemons_limit, server_limit);
        }
        ap_daemons_limit = server_limit;
    }
    else if (ap_daemons_limit < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00182)
                         "WARNING: MaxRequestWorkers of %d not allowed, "
                         "increasing to 1.", ap_daemons_limit);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00183)
                         "MaxRequestWorkers of %d not allowed, increasing to 1",
                         ap_daemons_limit);
        }
        ap_daemons_limit = 1;
    }

    /* ap_daemons_to_start > ap_daemons_limit checked in prefork_run() */
    if (ap_daemons_to_start < 0) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00184)
                         "WARNING: StartServers of %d not allowed, "
                         "increasing to 1.", ap_daemons_to_start);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00185)
                         "StartServers of %d not allowed, increasing to 1",
                         ap_daemons_to_start);
        }
        ap_daemons_to_start = 1;
    }

    if (ap_daemons_min_free < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00186)
                         "WARNING: MinSpareServers of %d not allowed, "
                         "increasing to 1", ap_daemons_min_free);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " to avoid almost certain server failure.");
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " Please read the documentation.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00187)
                         "MinSpareServers of %d not allowed, increasing to 1",
                         ap_daemons_min_free);
        }
        ap_daemons_min_free = 1;
    }

