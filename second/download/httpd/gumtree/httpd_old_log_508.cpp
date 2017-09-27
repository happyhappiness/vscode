ap_log_error(APLOG_MARK, APLOG_WARNING,
                             0, ap_server_conf,
                             "child process %ld still did not exit, "
                             "sending a SIGTERM",
                             (long)pid);