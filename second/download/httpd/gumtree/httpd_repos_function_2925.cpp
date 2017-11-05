static apr_status_t send_brigade_blocking(apr_socket_t *s,
                                          apr_bucket_brigade *bb,
                                          apr_size_t *bytes_written,
                                          conn_rec *c)
{
    apr_status_t rv;

    rv = APR_SUCCESS;
    while (!APR_BRIGADE_EMPTY(bb)) {
        rv = send_brigade_nonblocking(s, bb, bytes_written, c);
        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_EAGAIN(rv)) {
                /* Wait until we can send more data */
                apr_int32_t nsds;
                apr_interval_time_t timeout;
                apr_pollfd_t pollset;

                pollset.p = c->pool;
                pollset.desc_type = APR_POLL_SOCKET;
                pollset.reqevents = APR_POLLOUT;
                pollset.desc.s = s;
                apr_socket_timeout_get(s, &timeout);
                rv = apr_poll(&pollset, 1, &nsds, timeout);
                if (rv != APR_SUCCESS) {
                    break;
                }
            }
            else {
                break;
            }
        }
    }
    return rv;
}