            CloseHandle(events[2]);
            return 1;
        }
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00334)
                 "Child: Accept thread listening on %s:%d using AcceptFilter %s",
                 lr->bind_addr->hostname ? lr->bind_addr->hostname : "*",
                 lr->bind_addr->port, accf_name);

    while (!shutdown_in_progress) {
        if (!context) {
            int timeout;

            context = mpm_get_completion_context(&timeout);
