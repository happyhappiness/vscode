        }
    }

    return num_listeners;
}

AP_DECLARE(apr_status_t) ap_duplicate_listeners(apr_pool_t *p, server_rec *s,
                                                ap_listen_rec ***buckets,
                                                int *num_buckets)
{
    static int warn_once;
    int i;
    apr_status_t stat;
    int use_nonblock = 0;
    ap_listen_rec *lr;

    if (*num_buckets < 1) {
        *num_buckets = 1;
        if (ap_listencbratio > 0) {
#ifdef _SC_NPROCESSORS_ONLN
            if (ap_have_so_reuseport) {
                int num_online_cores = sysconf(_SC_NPROCESSORS_ONLN),
                    val = num_online_cores / ap_listencbratio;
                if (val > 1) {
                    *num_buckets = val;
                }
                ap_log_perror(APLOG_MARK, APLOG_INFO, 0, p, APLOGNO(02819)
                              "Using %i listeners bucket(s) based on %i "
                              "online CPU cores and a ratio of %i",
                              *num_buckets, num_online_cores,
                              ap_listencbratio);
            }
            else
#endif
            if (!warn_once) {
                ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, p, APLOGNO(02820)
                              "ListenCoresBucketsRatio ignored without "
                              "SO_REUSEPORT and _SC_NPROCESSORS_ONLN "
                              "support: using a single listeners bucket");
                warn_once = 1;
            }
        }
    }

    *buckets = apr_pcalloc(p, *num_buckets * sizeof(ap_listen_rec *));
    (*buckets)[0] = ap_listeners;

    for (i = 1; i < *num_buckets; i++) {
        ap_listen_rec *last = NULL;
        lr = ap_listeners;
        while (lr) {
            ap_listen_rec *duplr;
            char *hostname;
            apr_port_t port;
            apr_sockaddr_t *sa;
            duplr = apr_palloc(p, sizeof(ap_listen_rec));
            duplr->slave = NULL;
            duplr->protocol = apr_pstrdup(p, lr->protocol);
            hostname = apr_pstrdup(p, lr->bind_addr->hostname);
            port = lr->bind_addr->port;
            apr_sockaddr_info_get(&sa, hostname, APR_UNSPEC, port, 0, p);
            duplr->bind_addr = sa;
            duplr->next = NULL;
            stat = apr_socket_create(&duplr->sd, duplr->bind_addr->family,
                                     SOCK_STREAM, 0, p);
            if (stat != APR_SUCCESS) {
                ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, p, APLOGNO(02640)
                            "ap_duplicate_listeners: for address %pI, "
                            "cannot duplicate a new socket!",
                            duplr->bind_addr);
                return stat;
            }
            make_sock(p, duplr);
#if AP_NONBLOCK_WHEN_MULTI_LISTEN
            use_nonblock = (ap_listeners && ap_listeners->next);
            stat = apr_socket_opt_set(duplr->sd, APR_SO_NONBLOCK, use_nonblock);
            if (stat != APR_SUCCESS) {
                ap_log_perror(APLOG_MARK, APLOG_CRIT, stat, p, APLOGNO(02641)
                              "unable to control socket non-blocking status");
                return stat;
            }
#endif
            ap_apply_accept_filter(p, duplr, s);

            if (last == NULL) {
                (*buckets)[i] = last = duplr;
            }
            else {
                last->next = duplr;
                last = duplr;
            }
            lr = lr->next;
        }
    }

    ap_listen_buckets = *buckets;
    ap_num_listen_buckets = *num_buckets;
    return APR_SUCCESS;
}

AP_DECLARE_NONSTD(void) ap_close_listeners(void)
{
    int i;

    ap_close_listeners_ex(ap_listeners);

    /* Start from index 1 since either ap_duplicate_listeners()
     * was called and ap_listen_buckets[0] == ap_listeners, or
     * it wasn't and ap_num_listen_buckets == 0.
     */
    for (i = 1; i < ap_num_listen_buckets; i++) {
        ap_close_listeners_ex(ap_listen_buckets[i]);
    }
}

AP_DECLARE_NONSTD(void) ap_close_listeners_ex(ap_listen_rec *listeners)
{
    ap_listen_rec *lr;
    for (lr = listeners; lr; lr = lr->next) {
        apr_socket_close(lr->sd);
        lr->active = 0;
    }
}

AP_DECLARE_NONSTD(int) ap_close_selected_listeners(ap_slave_t *slave)
{
    ap_listen_rec *lr;
    int n = 0;

    for (lr = ap_listeners; lr; lr = lr->next) {
