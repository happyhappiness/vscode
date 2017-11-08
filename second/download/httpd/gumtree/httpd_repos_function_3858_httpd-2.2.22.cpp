static apr_status_t impl_pollcb_poll(apr_pollcb_t *pollcb,
                                     apr_interval_time_t timeout,
                                     apr_pollcb_cb_t func,
                                     void *baton)
{
    int ret, i;
    apr_status_t rv = APR_SUCCESS;
    
    if (timeout > 0) {
        timeout /= 1000;
    }
    
    ret = epoll_wait(pollcb->fd, pollcb->pollset.epoll, pollcb->nalloc,
                     timeout);
    if (ret < 0) {
        rv = apr_get_netos_error();
    }
    else if (ret == 0) {
        rv = APR_TIMEUP;
    }
    else {
        for (i = 0; i < ret; i++) {
            apr_pollfd_t *pollfd = (apr_pollfd_t *)(pollcb->pollset.epoll[i].data.ptr);
            pollfd->rtnevents = get_epoll_revent(pollcb->pollset.epoll[i].events);

            rv = func(baton, pollfd);
            if (rv) {
                return rv;
            }
        }
    }
    
    return rv;
}