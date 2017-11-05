static int ap_listen_open(apr_pool_t *pool, apr_port_t port)
{
    ap_listen_rec *lr;
    ap_listen_rec *next;
    int num_open;
    const char *userdata_key = "ap_listen_open";
    void *data;

    /* Don't allocate a default listener.  If we need to listen to a
     * port, then the user needs to have a Listen directive in their
     * config file.
     */
    num_open = 0;
    for (lr = ap_listeners; lr; lr = lr->next) {
        if (lr->active) {
            ++num_open;
        }
        else {
            if (make_sock(pool, lr) == APR_SUCCESS) {
                ++num_open;
                lr->active = 1;
            }
            else {
                /* fatal error */
                return -1;
            }
        }
    }

    /* close the old listeners */
    for (lr = old_listeners; lr; lr = next) {
        apr_socket_close(lr->sd);
        lr->active = 0;
        next = lr->next;
    }
    old_listeners = NULL;

#if AP_NONBLOCK_WHEN_MULTI_LISTEN
    /* if multiple listening sockets, make them non-blocking so that
     * if select()/poll() reports readability for a reset connection that
     * is already forgotten about by the time we call accept, we won't
     * be hung until another connection arrives on that port
     */
    if (ap_listeners && ap_listeners->next) {
        for (lr = ap_listeners; lr; lr = lr->next) {
            apr_status_t status;

            status = apr_socket_opt_set(lr->sd, APR_SO_NONBLOCK, 1);
            if (status != APR_SUCCESS) {
                ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_ERR, status, pool,
                              "ap_listen_open: unable to make socket non-blocking");
                return -1;
            }
        }
    }
#endif /* AP_NONBLOCK_WHEN_MULTI_LISTEN */

    /* we come through here on both passes of the open logs phase
     * only register the cleanup once... otherwise we try to close
     * listening sockets twice when cleaning up prior to exec
     */
    apr_pool_userdata_get(&data, userdata_key, pool);
    if (!data) {
        apr_pool_userdata_set((const void *)1, userdata_key,
                              apr_pool_cleanup_null, pool);
        apr_pool_cleanup_register(pool, NULL, apr_pool_cleanup_null,
                                  close_listeners_on_exec);
    }

    return num_open ? 0 : -1;
}