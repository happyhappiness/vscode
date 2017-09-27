    /* XXX If specifying SIG_IGN is guaranteed to unblock a syscall,
     *     then we don't need this goofy function.
     */
}


#if HAVE_SERF
static apr_status_t s_socket_add(void *user_baton,
                                 apr_pollfd_t *pfd,
                                 void *serf_baton)
{
    s_baton_t *s = (s_baton_t*)user_baton;
    /* XXXXX: recycle listener_poll_types */
    listener_poll_type *pt = malloc(sizeof(*pt));
    pt->type = PT_SERF;
    pt->baton = serf_baton;
    pfd->client_data = pt;
    return apr_pollset_add(s->pollset, pfd);
}

static apr_status_t s_socket_remove(void *user_baton,
                                    apr_pollfd_t *pfd,
                                    void *serf_baton)
{
    s_baton_t *s = (s_baton_t*)user_baton;
    listener_poll_type *pt = pfd->client_data;
    free(pt);
    return apr_pollset_remove(s->pollset, pfd);
}
#endif

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
