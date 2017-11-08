static int ap_listen_open(apr_pool_t *pool, apr_port_t port)
{
    ap_listen_rec *lr;
    ap_listen_rec *next;
    int num_open;

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

    apr_pool_cleanup_register(pool, NULL, apr_pool_cleanup_null,
                              close_listeners_on_exec);

    return num_open ? 0 : -1;
}