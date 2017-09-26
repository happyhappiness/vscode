ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                         "Child %lu: Listening on port %d.", my_pid, lr->bind_addr->port);