        if (lr->sd != NULL) {
            apr_os_sock_get(&nsd, lr->sd);
            FD_SET(nsd, &listenfds);
            if (listenmaxfd == INVALID_SOCKET || nsd > listenmaxfd) {
                listenmaxfd = nsd;
            }
        }
    }

    head_listener = ap_listeners;

    while (!shutdown_in_progress) {
