static apr_status_t impl_pollcb_poll(apr_pollcb_t *pollcb,
                                     apr_interval_time_t timeout,
                                     apr_pollcb_cb_t func,
                                     void *baton)
{
    int ret;
    apr_status_t rv = APR_SUCCESS;
    apr_uint32_t i;

#ifdef WIN32
    /* WSAPoll() requires at least one socket. */
    if (pollcb->nelts == 0) {
        if (timeout > 0) {
            apr_sleep(timeout);
            return APR_TIMEUP;
        }
        return APR_SUCCESS;
    }
    if (timeout > 0) {
        timeout /= 1000;
    }
    ret = WSAPoll(pollcb->pollset.ps, pollcb->nelts, (int)timeout);
#else
    if (timeout > 0) {
        timeout /= 1000;
    }
    ret = poll(pollcb->pollset.ps, pollcb->nelts, timeout);
#endif
    if (ret < 0) {
        return apr_get_netos_error();
    }
    else if (ret == 0) {
        return APR_TIMEUP;
    }
    else {
        for (i = 0; i < pollcb->nelts; i++) {
            if (pollcb->pollset.ps[i].revents != 0) {
                apr_pollfd_t *pollfd = pollcb->copyset[i];
                pollfd->rtnevents = get_revent(pollcb->pollset.ps[i].revents);                    
                rv = func(baton, pollfd);
                if (rv) {
                    return rv;
                }
            }
        }
    }
    return rv;
}