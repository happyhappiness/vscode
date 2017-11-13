ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MaxClients of %d is not an integer "
                         "multiple of", max_clients);