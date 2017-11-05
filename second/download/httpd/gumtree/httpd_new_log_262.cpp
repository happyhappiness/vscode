ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    " Automatically lowering MaxClients to %d.  To increase,",
                    server_limit * ap_threads_per_child);