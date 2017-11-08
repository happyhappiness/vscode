apr_status_t apr_wait_for_io_or_timeout(apr_file_t *f, apr_socket_t *s,
                                           int for_read)
{
    apr_interval_time_t timeout;
    apr_pollfd_t pollset;
    int srv, n;
    int type = for_read ? APR_POLLIN : APR_POLLOUT;

    /* TODO - timeout should be less each time through this loop */
    if (f) {
        pollset.desc_type = APR_POLL_FILE;
        pollset.desc.f = f;
        pollset.p = f->pool;
        timeout = f->timeout;
    }
    else {
        pollset.desc_type = APR_POLL_SOCKET;
        pollset.desc.s = s;
        pollset.p = s->cntxt;
        timeout = s->timeout;
    }
    pollset.reqevents = type;

    do {
        srv = apr_poll(&pollset, 1, &n, timeout);

        if (n == 1 && pollset.rtnevents & type) {
            return APR_SUCCESS;
        }
    } while (APR_STATUS_IS_EINTR(srv));

    return srv;
}