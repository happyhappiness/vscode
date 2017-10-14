ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
                 "Child %d: Accept thread listening on %s:%d using %s", my_pid,
                 lr->bind_addr->hostname ? lr->bind_addr->hostname : "*",
                 lr->bind_addr->port, accf_name);