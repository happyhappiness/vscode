static apr_status_t init_pollset(apr_pool_t *p)
{
#if HAVE_SERF
    s_baton_t *baton = NULL;
#endif
    apr_status_t rv;
    ap_listen_rec *lr;
    listener_poll_type *pt;

    rv = apr_thread_mutex_create(&timeout_mutex, APR_THREAD_MUTEX_DEFAULT, p);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                     "creation of the timeout mutex failed.");
        return rv;
    }

    APR_RING_INIT(&timeout_head, conn_state_t, timeout_list);
    APR_RING_INIT(&keepalive_timeout_head, conn_state_t, timeout_list);

    /* Create the main pollset */
    rv = apr_pollset_create(&event_pollset,
                            threads_per_child,
                            p, APR_POLLSET_THREADSAFE | APR_POLLSET_NOCOPY);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                     "apr_pollset_create with Thread Safety failed.");
        return rv;
    }

    for (lr = ap_listeners; lr != NULL; lr = lr->next) {
        apr_pollfd_t *pfd = apr_palloc(p, sizeof(*pfd));
        pt = apr_pcalloc(p, sizeof(*pt));
        pfd->desc_type = APR_POLL_SOCKET;
        pfd->desc.s = lr->sd;
        pfd->reqevents = APR_POLLIN;

        pt->type = PT_ACCEPT;
        pt->baton = lr;

        pfd->client_data = pt;

        apr_socket_opt_set(pfd->desc.s, APR_SO_NONBLOCK, 1);
        apr_pollset_add(event_pollset, pfd);

        lr->accept_func = ap_unixd_accept;
    }

#if HAVE_SERF
    baton = apr_pcalloc(p, sizeof(*baton));
    baton->pollset = event_pollset;
    /* TODO: subpools, threads, reuse, etc.  -- currently use malloc() inside :( */
    baton->pool = p;

    g_serf = serf_context_create_ex(baton,
                                    s_socket_add,
                                    s_socket_remove, p);

    ap_register_provider(p, "mpm_serf",
                         "instance", "0", g_serf);

#endif

    return APR_SUCCESS;
}