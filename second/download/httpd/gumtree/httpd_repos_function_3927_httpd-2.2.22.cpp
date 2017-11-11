apr_status_t apr_socket_timeout_set(apr_socket_t *sock, apr_interval_time_t t)
{
    apr_status_t stat;

    /* If our new timeout is non-negative and our old timeout was
     * negative, then we need to ensure that we are non-blocking.
     * Conversely, if our new timeout is negative and we had
     * non-negative timeout, we must make sure our socket is blocking.
     * We want to avoid calling fcntl more than necessary on the
     * socket.
     */
    if (t >= 0 && sock->timeout < 0) {
        if (apr_is_option_set(sock, APR_SO_NONBLOCK) != 1) {
            if ((stat = sononblock(sock->socketdes)) != APR_SUCCESS) {
                return stat;
            }
            apr_set_option(sock, APR_SO_NONBLOCK, 1);
        }
    } 
    else if (t < 0 && sock->timeout >= 0) {
        if (apr_is_option_set(sock, APR_SO_NONBLOCK) != 0) { 
            if ((stat = soblock(sock->socketdes)) != APR_SUCCESS) { 
                return stat; 
            }
            apr_set_option(sock, APR_SO_NONBLOCK, 0);
        } 
    }
    /* must disable the incomplete read support if we disable
     * a timeout
     */
    if (t <= 0) {
        sock->options &= ~APR_INCOMPLETE_READ;
    }
    sock->timeout = t;
    return APR_SUCCESS;
}