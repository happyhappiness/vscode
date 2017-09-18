ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    " of ThreadsPerChild (%d), lowering MaxClients to %d",
                    ap_threads_per_child,
                    ap_daemons_limit * ap_threads_per_child);