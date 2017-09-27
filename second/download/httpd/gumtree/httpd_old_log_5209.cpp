ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                         "WARNING: MaxClients of %d would require %d "
                         "servers and ", max_clients, ap_daemons_limit);