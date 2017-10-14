ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00180)
                         "WARNING: MaxRequestWorkers of %d exceeds ServerLimit "
                         "value of %d servers, decreasing MaxRequestWorkers to %d. "
                         "To increase, please see the ServerLimit directive.",
                         ap_daemons_limit, server_limit, server_limit);