static apr_status_t impl_pollset_poll(apr_pollset_t *pollset,
                                      apr_interval_time_t timeout,
                                      apr_int32_t *num,
                                      const apr_pollfd_t **descriptors)
{
    int ret, i, j;
    struct timespec tv, *tvptr;
    apr_status_t rv = APR_SUCCESS;
    apr_pollfd_t fd;

    if (timeout < 0) {
        tvptr = NULL;
    }
    else {
        tv.tv_sec = (long) apr_time_sec(timeout);
        tv.tv_nsec = (long) apr_time_usec(timeout) * 1000;
        tvptr = &tv;
    }

    ret = kevent(pollset->p->kqueue_fd, NULL, 0, pollset->p->ke_set,
                 pollset->p->setsize, tvptr);
    (*num) = ret;
    if (ret < 0) {
        rv = apr_get_netos_error();
    }
    else if (ret == 0) {
        rv = APR_TIMEUP;
    }
    else {
        for (i = 0, j = 0; i < ret; i++) {
            fd = (((pfd_elem_t*)(pollset->p->ke_set[i].udata))->pfd);
            if ((pollset->flags & APR_POLLSET_WAKEABLE) &&
                fd.desc_type == APR_POLL_FILE &&
                fd.desc.f == pollset->wakeup_pipe[0]) {
                apr_pollset_drain_wakeup_pipe(pollset);
                rv = APR_EINTR;
            }
            else {
                pollset->p->result_set[j] = fd;
                pollset->p->result_set[j].rtnevents =
                        get_kqueue_revent(pollset->p->ke_set[i].filter,
                                          pollset->p->ke_set[i].flags);
                j++;
            }
        }
        if ((*num = j)) { /* any event besides wakeup pipe? */
            rv = APR_SUCCESS;
            if (descriptors) {
                *descriptors = pollset->p->result_set;
            }
        }
    }


    pollset_lock_rings();

    /* Shift all PFDs in the Dead Ring to the Free Ring */
    APR_RING_CONCAT(&(pollset->p->free_ring), &(pollset->p->dead_ring),
                    pfd_elem_t, link);

    pollset_unlock_rings();

    return rv;
}