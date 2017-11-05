ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MaxClients of %d not allowed, "
                         "increasing to 1.", ap_daemons_limit);