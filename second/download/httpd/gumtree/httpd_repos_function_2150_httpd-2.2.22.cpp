static int open_listeners(apr_pool_t *pool)
{
    ap_listen_rec *lr;
    ap_listen_rec *next;
    ap_listen_rec *previous;
    int num_open;
    const char *userdata_key = "ap_open_listeners";
    void *data;
#if AP_NONBLOCK_WHEN_MULTI_LISTEN
    int use_nonblock;
#endif

    /* Don't allocate a default listener.  If we need to listen to a
     * port, then the user needs to have a Listen directive in their
     * config file.
     */
    num_open = 0;
    previous = NULL;
    for (lr = ap_listeners; lr; previous = lr, lr = lr->next) {
        if (lr->active) {
            ++num_open;
        }
        else {
#if APR_HAVE_IPV6
            ap_listen_rec *cur;
            int v6only_setting;
            int skip = 0;

            /* If we have the unspecified IPv4 address (0.0.0.0) and
             * the unspecified IPv6 address (::) is next, we need to
             * swap the order of these in the list. We always try to
             * bind to IPv6 first, then IPv4, since an IPv6 socket
             * might be able to receive IPv4 packets if V6ONLY is not
             * enabled, but never the other way around.
             * Note: In some configurations, the unspecified IPv6 address
             * could be even later in the list.  This logic only corrects
             * the situation where it is next in the list, such as when
             * apr_sockaddr_info_get() returns an IPv4 and an IPv6 address,
             * in that order.
             */
            if (lr->next != NULL
                && IS_INADDR_ANY(lr->bind_addr)
                && lr->bind_addr->port == lr->next->bind_addr->port
                && IS_IN6ADDR_ANY(lr->next->bind_addr)) {
                /* Exchange lr and lr->next */
                next = lr->next;
                lr->next = next->next;
                next->next = lr;
                if (previous) {
                    previous->next = next;
                }
                else {
                    ap_listeners = next;
                }
                lr = next;
            }

            /* If we are trying to bind to 0.0.0.0 and a previous listener
             * was :: on the same port and in turn that socket does not have
             * the IPV6_V6ONLY flag set; we must skip the current attempt to
             * listen (which would generate an error). IPv4 will be handled
             * on the established IPv6 socket.
             */
            if (IS_INADDR_ANY(lr->bind_addr)) {
                for (cur = ap_listeners; cur != lr; cur = cur->next) {
                    if (lr->bind_addr->port == cur->bind_addr->port
                        && IS_IN6ADDR_ANY(cur->bind_addr)
                        && apr_socket_opt_get(cur->sd, APR_IPV6_V6ONLY,
                                              &v6only_setting) == APR_SUCCESS
                        && v6only_setting == 0) {

                        /* Remove the current listener from the list */
                        previous->next = lr->next;
                        lr = previous; /* maintain current value of previous after
                                        * post-loop expression is evaluated
                                        */
                        skip = 1;
                        break;
                    }
                }
                if (skip) {
                    continue;
                }
            }
#endif
            if (make_sock(pool, lr) == APR_SUCCESS) {
                ++num_open;
                lr->active = 1;
            }
            else {
#if APR_HAVE_IPV6
                /* If we tried to bind to ::, and the next listener is
                 * on 0.0.0.0 with the same port, don't give a fatal
                 * error. The user will still get a warning from make_sock
                 * though.
                 */
                if (lr->next != NULL
                    && IS_IN6ADDR_ANY(lr->bind_addr)
                    && lr->bind_addr->port == lr->next->bind_addr->port
                    && IS_INADDR_ANY(lr->next->bind_addr)) {

                    /* Remove the current listener from the 