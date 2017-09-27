ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, s, 
                     "Initialisation of global mutex %s in child process %"
                     APR_PID_T_FMT
                     " successful.",
                     st->lock_file, getpid());