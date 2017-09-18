ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    " large as ThreadsPerChild (%d). Automatically",
                    ap_threads_per_child);