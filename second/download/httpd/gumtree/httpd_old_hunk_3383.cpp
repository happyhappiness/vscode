     */
    if (!retained->first_server_limit) {
        retained->first_server_limit = server_limit;
    }
    else if (server_limit != retained->first_server_limit) {
        /* don't need a startup console version here */
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "changing ServerLimit to %d from original value of %d "
                     "not allowed during restart",
                     server_limit, retained->first_server_limit);
        server_limit = retained->first_server_limit;
    }

    if (ap_daemons_limit > server_limit) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MaxClients of %d exceeds ServerLimit "
                         "value of", ap_daemons_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " %d servers, decreasing MaxClients to %d.",
                         server_limit, server_limit);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " To increase, please see the ServerLimit "
                         "directive.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MaxClients of %d exceeds ServerLimit value "
                         "of %d, decreasing to match",
                         ap_daemons_limit, server_limit);
        }
        ap_daemons_limit = server_limit;
    }
    else if (ap_daemons_limit < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MaxClients of %d not allowed, "
                         "increasing to 1.", ap_daemons_limit);
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MaxClients of %d not allowed, increasing to 1",
                         ap_daemons_limit);
        }
        ap_daemons_limit = 1;
    }

    /* ap_daemons_to_start > ap_daemons_limit checked in prefork_run() */
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

    if (ap_daemons_min_free < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MinSpareServers of %d not allowed, "
                         "increasing to 1", ap_daemons_min_free);
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " to avoid almost certain server failure.");
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         " Please read the documentation.");
        } else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MinSpareServers of %d not allowed, increasing to 1",
                         ap_daemons_min_free);
        }
        ap_daemons_min_free = 1;
    }

