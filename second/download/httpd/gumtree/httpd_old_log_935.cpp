ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0,
                             ap_server_conf,
                             "long lost child came home! (pid %ld)",
                             (long)pid.pid);