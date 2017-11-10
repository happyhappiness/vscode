static apr_status_t impl_pollset_create(apr_pollset_t *pollset,
                                             apr_uint32_t size,
                                             apr_pool_t *p,
                                             apr_uint32_t flags)
{
    apr_status_t rv = APR_SUCCESS;
    pollset->p = apr_palloc(p, sizeof(apr_pollset_private_t));
#if APR_HAS_THREADS
    if (flags & APR_POLLSET_THREADSAFE &&
        ((rv = apr_thread_mutex_create(&pollset->p->ring_lock,
                                       APR_THREAD_MUTEX_DEFAULT,
                                       p)) != APR_SUCCESS)) {
        pollset->p = NULL;
        return rv;
    }
#else
    if (flags & APR_POLLSET_THREADSAFE) {
        pollset->p = NULL;
        return APR_ENOTIMPL;
    }
#endif
    pollset->p->waiting = 0;

    pollset->p->port_set = apr_palloc(p, size * sizeof(port_event_t));

    pollset->p->port_fd = port_create();

    if (pollset->p->port_fd < 0) {
        pollset->p = NULL;
        return apr_get_netos_error();
    }

    {
        int flags;

        if ((flags = fcntl(pollset->p->port_fd, F_GETFD)) == -1)
            return errno;

        flags |= FD_CLOEXEC;
        if (fcntl(pollset->p->port_fd, F_SETFD, flags) == -1)
            return errno;
    }

    pollset->p->result_set = apr_palloc(p, size * sizeof(apr_pollfd_t));

    APR_RING_INIT(&pollset->p->query_ring, pfd_elem_t, link);
    APR_RING_INIT(&pollset->p->add_ring, pfd_elem_t, link);
    APR_RING_INIT(&pollset->p->free_ring, pfd_elem_t, link);
    APR_RING_INIT(&pollset->p->dead_ring, pfd_elem_t, link);

    return rv;
}