static apr_status_t init_pollset(apr_pool_t *p)
{
    ap_listen_rec *lr;
    listener_poll_type *pt;
    int i = 0;

    TO_QUEUE_INIT(write_completion_q);
    TO_QUEUE_INIT(keepalive_q);
    TO_QUEUE_INIT(linger_q);
    TO_QUEUE_INIT(short_linger_q);

    listener_pollfd = apr_palloc(p, sizeof(apr_pollfd_t) * num_listensocks);
    for (lr = ap_listeners; lr != NULL; lr = lr->next, i++) {
        apr_pollfd_t *pfd;
        AP_DEBUG_ASSERT(i < num_listensocks);
        pfd = &listener_pollfd[i];
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

    return APR_SUCCESS;
}