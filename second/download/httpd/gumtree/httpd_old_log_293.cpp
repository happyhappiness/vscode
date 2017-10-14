ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
                         "sigaction(SIGABRT)");