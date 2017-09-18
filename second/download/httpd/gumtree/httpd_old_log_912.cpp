ap_log_error(APLOG_MARK,APLOG_NOTICE | APLOG_NOERRNO, rv, ap_server_conf, 
                     "Child %d: Released the start mutex", my_pid);