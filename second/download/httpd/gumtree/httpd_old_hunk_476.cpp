    ap_listen_rec *lr;

    pconf = p;
    ap_server_conf = s;

    if ((num_listensocks = ap_setup_listeners(ap_server_conf)) < 1) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ALERT|APLOG_STARTUP, 0,
                     NULL, "no listening sockets available, shutting down");
        return DONE;
    }

#if APR_O_NONBLOCK_INHERITED
    for(lr = ap_listeners ; lr != NULL ; lr = lr->next) {
