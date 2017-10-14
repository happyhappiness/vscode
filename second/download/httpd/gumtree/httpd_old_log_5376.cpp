ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: ServerLimit of %d exceeds compile-time "
                         "limit of", server_limit);