static apr_status_t impl_pollset_create(apr_pollset_t *pollset,
                                        apr_uint32_t size,
                                        apr_pool_t *p,
                                        apr_uint32_t flags)
{
    apr_status_t rv;
    int fd;

#ifdef HAVE_EPOLL_CREATE1
    fd = epoll_create1(EPOLL_CLOEXEC);
#else
    fd = epoll_create(size);
#endif
    if (fd < 0) {
        pollset->p = NULL;
        return apr_get_netos_error();
    }

#ifndef HAVE_EPOLL_CREATE1
    {
        int flags;

        if ((flags = fcntl(fd, F_GETFD)) == -1)
            return errno;

        flags |= FD_CLOEXEC;
        if (fcntl(fd, F_SETFD, flags) == -1)
            return errno;
    }
#endif

    pollset->p = apr_palloc(p, sizeof(apr_pollset_private_t));
#if APR_HAS_THREADS
    if ((flags & APR_POLLSET_THREADSAFE) &&
        !(flags & APR_POLLSET_NOCOPY) &&
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
    pollset->p->epoll_fd = fd;
    pollset->p->pollset = apr_palloc(p, size * sizeof(struct epoll_event));
    pollset->p->result_set = apr_palloc(p, size * sizeof(apr_pollfd_t));

    if (!(flags & APR_POLLSET_NOCOPY)) {
        APR_RING_INIT(&pollset->p->query_ring, pfd_elem_t, link);
        APR_RING_INIT(&pollset->p->free_ring, pfd_elem_t, link);
        APR_RING_INIT(&pollset->p->dead_ring, pfd_elem_t, link);
    }
    return APR_SUCCESS;
}