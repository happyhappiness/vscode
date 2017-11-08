static apr_status_t impl_pollcb_poll(apr_pollcb_t *pollcb,
                                     apr_interval_time_t timeout,
                                     apr_pollcb_cb_t func,
                                     void *baton)
{
    int ret, i;
    struct timespec tv, *tvptr;
    apr_status_t rv = APR_SUCCESS;
    
    if (timeout < 0) {
        tvptr = NULL;
    }
    else {
        tv.tv_sec = (long) apr_time_sec(timeout);
        tv.tv_nsec = (long) apr_time_usec(timeout) * 1000;
        tvptr = &tv;
    }
    
    ret = kevent(pollcb->fd, NULL, 0, pollcb->pollset.ke, 2 * pollcb->nalloc,
                 tvptr);

    if (ret < 0) {
        rv = apr_get_netos_error();
    }
    else if (ret == 0) {
        rv = APR_TIMEUP;
    }
    else {
        for (i = 0; i < ret; i++) {
            apr_pollfd_t *pollfd = (apr_pollfd_t *)(pollcb->pollset.ke[i].udata);
            
            pollfd->rtnevents = get_kqueue_revent(pollcb->pollset.ke[i].filter,
                                                  pollcb->pollset.ke[i].flags);
            
            rv = func(baton, pollfd);
            
            if (rv) {
                return rv;
            }
        }
    }

    return rv;
}