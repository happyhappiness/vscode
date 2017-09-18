ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR,
                             0, ap_server_conf,
                             "child process %ld still did not exit, "
                             "sending a SIGKILL",
                             (long)pid);