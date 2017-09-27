        if (lr->sd != NULL) {
            apr_os_sock_get(&nsd, lr->sd);
            FD_SET(nsd, &listenfds);
            if (listenmaxfd == INVALID_SOCKET || nsd > listenmaxfd) {
                listenmaxfd = nsd;
            }
            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                         "Child %d: Listening on port %d.", my_pid, lr->bind_addr->port);
        }
    }

    head_listener = ap_listeners;

    while (!shutdown_in_progress) {
