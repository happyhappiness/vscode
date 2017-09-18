ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                     "WARNING: ThreadsPerChild of %d exceeds compile time"
                     " limit of %d threads,", ap_threads_per_child, 
                     HARD_THREAD_LIMIT);