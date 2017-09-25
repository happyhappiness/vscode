    max_clients = atoi(arg);
    if (max_clients < ap_threads_per_child) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    "WARNING: MaxClients (%d) must be at least as large",
                    max_clients);
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    " large as ThreadsPerChild (%d). Automatically",
                    ap_threads_per_child);
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    " increasing MaxClients to %d.",
                    ap_threads_per_child);
       max_clients = ap_threads_per_child;
    }
