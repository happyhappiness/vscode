    FD_ZERO(&listenfds);
    for (lr = ap_listeners; lr; lr = lr->next) {
        if (lr->sd != NULL) {
            apr_os_sock_get(&nsd, lr->sd);
            FD_SET(nsd, &listenfds);
            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                         "Child %lu: Listening on port %d.", my_pid, lr->bind_addr->port);
        }
    }

    head_listener = ap_listeners;

    while (!shutdown_in_progress) {
