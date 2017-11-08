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
        /* Use non-blocking listen sockets so that we
           never get hung up. */
        apr_socket_opt_set(lr->sd, APR_SO_NONBLOCK, 1);
    }
    return 0;
}