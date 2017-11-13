static int setup_listeners(server_rec *s)
{
    ap_listen_rec *lr;
    int sockdes;

    if (ap_setup_listeners(s) < 1 ) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, 0, s,
            "no listening sockets available, shutting down");
        return -1;
    }

    listenmaxfd = -1;
    FD_ZERO(&listenfds);
    for (lr = ap_listeners; lr; lr = lr->next) {
        apr_os_sock_get(&sockdes, lr->sd);
        FD_SET(sockdes, &listenfds);
        if (sockdes > listenmaxfd) {
            listenmaxfd = sockdes;
        }
    }
    return 0;
}