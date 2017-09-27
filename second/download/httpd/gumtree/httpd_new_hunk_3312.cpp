    /* XXX If specifying SIG_IGN is guaranteed to unblock a syscall,
     *     then we don't need this goofy function.
     */
}


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
