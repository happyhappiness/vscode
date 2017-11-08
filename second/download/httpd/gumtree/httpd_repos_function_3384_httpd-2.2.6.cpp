static apr_int16_t get_kqueue_revent(apr_int16_t event, apr_int16_t flags)
{
    apr_int16_t rv = 0;

    if (event == EVFILT_READ)
        rv |= APR_POLLIN;
    if (event == EVFILT_WRITE)
        rv |= APR_POLLOUT;
    if (flags & EV_EOF)
        rv |= APR_POLLHUP;
    if (flags & EV_ERROR)
        rv |= APR_POLLERR;

    return rv;
}