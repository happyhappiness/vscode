#if AP_NONBLOCK_WHEN_MULTI_LISTEN
    /* if multiple listening sockets, make them non-blocking so that
     * if select()/poll() reports readability for a reset connection that
     * is already forgotten about by the time we call accept, we won't
     * be hung until another connection arrives on that port
     */
    use_nonblock = (ap_listeners && ap_listeners->next);
    for (lr = ap_listeners; lr; lr = lr->next) {
        apr_status_t status;

        status = apr_socket_opt_set(lr->sd, APR_SO_NONBLOCK, use_nonblock);
        if (status != APR_SUCCESS) {
            ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_ERR, status, pool,
                          "unable to control socket non-blocking status");
            return -1;
        }
    }
#endif /* AP_NONBLOCK_WHEN_MULTI_LISTEN */

    /* we come through here on both passes of the open logs phase
     * only register the cleanup once... otherwise we try to close
