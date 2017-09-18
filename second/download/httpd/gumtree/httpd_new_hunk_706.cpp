                     NULL, "no listening sockets available, shutting down");
        return DONE;
    }

#if APR_O_NONBLOCK_INHERITED
    for(lr = ap_listeners ; lr != NULL ; lr = lr->next) {
        apr_socket_opt_set(lr->sd, APR_SO_NONBLOCK, 1);
    }
#endif /* APR_O_NONBLOCK_INHERITED */

    if (!one_process) {
        if ((rv = ap_mpm_pod_open(pconf, &pod))) {
            ap_log_error(APLOG_MARK, APLOG_CRIT|APLOG_STARTUP, rv, NULL,
