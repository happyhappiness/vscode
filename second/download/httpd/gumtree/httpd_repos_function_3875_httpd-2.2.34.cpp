static apr_status_t impl_pollset_poll(apr_pollset_t *pollset,
                                      apr_interval_time_t timeout,
                                      apr_int32_t *num,
                                      const apr_pollfd_t **descriptors)
{
    int ret;
    apr_status_t rv = APR_SUCCESS;

#ifdef WIN32
    /* WSAPoll() requires at least one socket. */
    if (pollset->nelts == 0) {
        *num = 0;
        if (timeout > 0) {
            apr_sleep(timeout);
            return APR_TIMEUP;
        }
        return APR_SUCCESS;
    }
    if (timeout > 0) {
        timeout /= 1000;
    }
    ret = WSAPoll(pollset->p->pollset, pollset->nelts, (int)timeout);
#else
    if (timeout > 0) {
        timeout /= 1000;
    }
    ret = poll(pollset->p->pollset, pollset->nelts, timeout);
#endif
    (*num) = ret;
    if (ret < 0) {
        return apr_get_netos_error();
    }
    else if (ret == 0) {
        return APR_TIMEUP;
    }
    else {
        apr_uint32_t i, j;

        for (i = 0, j = 0; i < pollset->nelts; i++) {
            if (pollset->p->pollset[i].revents != 0) {
                /* Check if the polled descriptor is our
                 * wakeup pipe. In that case do not put it result set.
                 */
                if ((pollset->flags & APR_POLLSET_WAKEABLE) &&
                    pollset->p->query_set[i].desc_type == APR_POLL_FILE &&
                    pollset->p->query_set[i].desc.f == pollset->wakeup_pipe[0]) {
                        apr_pollset_drain_wakeup_pipe(pollset);
                        rv = APR_EINTR;
                }
                else {
                    pollset->p->result_set[j] = pollset->p->query_set[i];
                    pollset->p->result_set[j].rtnevents =
                        get_revent(pollset->p->pollset[i].revents);
                    j++;
                }
            }
        }
        if (((*num) = j) > 0)
            rv = APR_SUCCESS;
    }
    if (descriptors && (*num))
        *descriptors = pollset->p->result_set;
    return rv;
}