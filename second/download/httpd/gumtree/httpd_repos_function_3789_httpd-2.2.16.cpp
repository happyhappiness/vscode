static apr_status_t impl_pollset_poll(apr_pollset_t *pollset,
                                           apr_interval_time_t timeout,
                                           apr_int32_t *num,
                                           const apr_pollfd_t **descriptors)
{
    int ret, i, j;
    apr_status_t rv = APR_SUCCESS;
    apr_pollfd_t *fdptr;

    if (timeout > 0) {
        timeout /= 1000;
    }

    ret = epoll_wait(pollset->p->epoll_fd, pollset->p->pollset, pollset->nalloc,
                     timeout);
    (*num) = ret;

    if (ret < 0) {
        rv = apr_get_netos_error();
    }
    else if (ret == 0) {
        rv = APR_TIMEUP;
    }
    else {
        for (i = 0, j = 0; i < ret; i++) {
            if (pollset->flags & APR_POLLSET_NOCOPY) {
                fdptr = (apr_pollfd_t *)(pollset->p->pollset[i].data.ptr);
            }
            else {
                fdptr = &(((pfd_elem_t *) (pollset->p->pollset[i].data.ptr))->pfd);
            }
            /* Check if the polled descriptor is our
             * wakeup pipe. In that case do not put it result set.
             */
            if ((pollset->flags & APR_POLLSET_WAKEABLE) &&
                fdptr->desc_type == APR_POLL_FILE &&
                fdptr->desc.f == pollset->wakeup_pipe[0]) {
                apr_pollset_drain_wakeup_pipe(pollset);
                rv = APR_EINTR;
            }
            else {
                pollset->p->result_set[j] = *fdptr;
                pollset->p->result_set[j].rtnevents =
                    get_epoll_revent(pollset->p->pollset[i].events);
                j++;
            }
        }
        if (((*num) = j)) { /* any event besides wakeup pipe? */
            rv = APR_SUCCESS;

            if (descriptors) {
                *descriptors = pollset->p->result_set;
            }
        }
    }

    if (!(pollset->flags & APR_POLLSET_NOCOPY)) {
        pollset_lock_rings();

        /* Shift all PFDs in the Dead Ring to the Free Ring */
        APR_RING_CONCAT(&(pollset->p->free_ring), &(pollset->p->dead_ring), pfd_elem_t, link);

        pollset_unlock_rings();
    }

    return rv;
}