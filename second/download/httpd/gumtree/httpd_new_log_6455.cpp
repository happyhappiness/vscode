ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00300)
                         "WARNING: ServerLimit of %d exceeds compile-time "
                         "limit of %d servers, decreasing to %d.",
                         server_limit, MAX_SERVER_LIMIT, MAX_SERVER_LIMIT);