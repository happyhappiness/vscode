ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, APR_SUCCESS,
                             ap_server_conf, "removed PID file %s (pid=%ld)",
                             pidfile, GetCurrentProcessId());