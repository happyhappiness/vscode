static apr_int16_t get_kqueue_revent(apr_int16_t event, apr_int16_t flags)
{
    apr_int16_t rv = 0;

    if (event == EVFILT_READ)
        rv |= APR_POLLIN;
    else if (event == EVFILT_WRITE)
        rv |= APR_POLLOUT;
    if (flags & EV_EOF)
        rv |= APR_POLLHUP;
    /* APR_POLLPRI, APR_POLLERR, and APR_POLLNVAL are not handled by this
     * implementation.
     * TODO: See if EV_ERROR + certain system errors in the returned data field
     * should map to APR_POLLNVAL.
     */
    return rv;
}