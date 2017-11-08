static apr_int16_t get_epoll_revent(apr_int16_t event)
{
    apr_int16_t rv = 0;

    if (event & EPOLLIN)
        rv |= APR_POLLIN;
    if (event & EPOLLPRI)
        rv |= APR_POLLPRI;
    if (event & EPOLLOUT)
        rv |= APR_POLLOUT;
    if (event & EPOLLERR)
        rv |= APR_POLLERR;
    if (event & EPOLLHUP)
        rv |= APR_POLLHUP;
    /* APR_POLLNVAL is not handled by epoll. */

    return rv;
}