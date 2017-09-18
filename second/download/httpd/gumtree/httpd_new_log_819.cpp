ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    " increasing MaxClients to %d.",
                    ap_threads_per_child);