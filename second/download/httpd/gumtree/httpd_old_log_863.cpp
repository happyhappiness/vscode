ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
                    " lowering MaxThreads to %d.  To increase, please "
                    "see the", HARD_THREAD_LIMIT);