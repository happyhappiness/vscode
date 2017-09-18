ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    "WARNING: MaxClients of %d would require %d servers,",
                    max_clients, ap_daemons_limit);