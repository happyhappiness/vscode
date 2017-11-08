static apr_status_t impl_pollset_create(apr_pollset_t *pollset,
                                        apr_uint32_t size,
                                        apr_pool_t *p,
                                        apr_uint32_t flags)
{
    apr_status_t rv;
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

    /* POLLIN and POLLOUT are represented in different returned
     * events, so we need 2 entries per descriptor in the result set,
     * both for what is returned by kevent() and what is returned to
     * the caller of apr_pollset_poll() (since it doesn't spend the
     * CPU to coalesce separate APR_POLLIN and APR_POLLOUT events
     * for the same descriptor)
     */
    pollset->p->setsize = 2 * size;

    pollset->p->ke_set =
        (struct kevent *) apr_palloc(p, pollset->p->setsize * sizeof(struct kevent));

    memset(pollset->p->ke_set, 0, pollset->p->setsize * sizeof(struct kevent));

    pollset->p->kqueue_fd = kqueue();

    if (pollset->p->kqueue_fd == -1) {
        pollset->p = NULL;
        return apr_get_netos_error();
    }

    {
        int flags;

        if ((flags = fcntl(pollset->p->kqueue_fd, F_GETFD)) == -1) {
            rv = errno;
            close(pollset->p->kqueue_fd);
            pollset->p = NULL;
            return rv;
        }

        flags |= FD_CLOEXEC;
        if (fcntl(pollset->p->kqueue_fd, F_SETFD, flags) == -1) {
            rv = errno;
            close(pollset->p->kqueue_fd);
            pollset->p = NULL;
            return rv;
        }
    }

    pollset->p->result_set = apr_palloc(p, pollset->p->setsize * sizeof(apr_pollfd_t));

    APR_RING_INIT(&pollset->p->query_ring, pfd_elem_t, link);
    APR_RING_INIT(&pollset->p->free_ring, pfd_elem_t, link);
    APR_RING_INIT(&pollset->p->dead_ring, pfd_elem_t, link);

    return APR_SUCCESS;
}