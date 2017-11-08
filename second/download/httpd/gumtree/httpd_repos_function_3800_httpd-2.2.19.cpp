static apr_status_t impl_pollcb_poll(apr_pollcb_t *pollcb,
                                     apr_interval_time_t timeout,
                                     apr_pollcb_cb_t func,
                                     void *baton)
{
    apr_pollfd_t *pollfd;
    apr_status_t rv;
    unsigned int i, nget = 1;

    rv = call_port_getn(pollcb->fd, pollcb->pollset.port, pollcb->nalloc,
                        &nget, timeout);

    if (nget) {
        for (i = 0; i < nget; i++) {
            pollfd = (apr_pollfd_t *)(pollcb->pollset.port[i].portev_user);
            pollfd->rtnevents = get_revent(pollcb->pollset.port[i].portev_events);

            rv = func(baton, pollfd);
            if (rv) {
                return rv;
            }
            rv = apr_pollcb_add(pollcb, pollfd);
        }
    }

    return rv;
}