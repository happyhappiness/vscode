ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, s, 
                     "INIT global mutex %s in child %d ", st->lock_file, getpid());