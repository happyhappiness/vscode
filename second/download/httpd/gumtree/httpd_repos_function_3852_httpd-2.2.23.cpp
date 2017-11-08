static apr_int16_t get_epoll_event(apr_int16_t event)
{
    apr_int16_t rv = 0;

    if (event & APR_POLLIN)
        rv |= EPOLLIN;
    if (event & APR_POLLPRI)
        rv |= EPOLLPRI;
    if (event & APR_POLLOUT)
        rv |= EPOLLOUT;
    /* APR_POLLNVAL is not handled by epoll.  EPOLLERR and EPOLLHUP are return-only */

    return rv;
}