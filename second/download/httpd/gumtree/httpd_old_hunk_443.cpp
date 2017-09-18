    }

    /* It is ok to use ap_threads_per_child here because we are
     * sure that it gets set before MaxClients in the pre_config stage. */
    max_clients = atoi(arg);
    if (max_clients < ap_threads_per_child) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    "WARNING: MaxClients (%d) must be at least as large",
                    max_clients);
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    " large as ThreadsPerChild (%d). Automatically",
                    ap_threads_per_child);
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    " increasing MaxClients to %d.",
                    ap_threads_per_child);
       max_clients = ap_threads_per_child;
    }
    ap_daemons_limit = max_clients / ap_threads_per_child;
    if ((max_clients > 0) && (max_clients % ap_threads_per_child)) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    "WARNING: MaxClients (%d) is not an integer multiple",
                    max_clients);
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    " of ThreadsPerChild (%d), lowering MaxClients to %d",
                    ap_threads_per_child,
                    ap_daemons_limit * ap_threads_per_child);
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    " for a maximum of %d child processes,",
                    ap_daemons_limit);
       max_clients = ap_daemons_limit * ap_threads_per_child; 
    }
    if (ap_daemons_limit > server_limit) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    "WARNING: MaxClients of %d would require %d servers,",
                    max_clients, ap_daemons_limit);
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    " and would exceed the ServerLimit value of %d.",
                    server_limit);
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    " Automatically lowering MaxClients to %d.  To increase,",
                    server_limit);
       ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    " please see the ServerLimit directive.");
       ap_daemons_limit = server_limit;
    } 
    else if (ap_daemons_limit < 1) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                     "WARNING: Require MaxClients > 0, setting to 1");
        ap_daemons_limit = 1;
    }
    return NULL;
}

