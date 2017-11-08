static apr_int16_t get_revent(apr_int16_t event)
{
    DBG_BUFF
    apr_int16_t rv = 0;
    DBG(4, "entered\n");

    if (event & POLLIN)
        rv |= APR_POLLIN;
    if (event & POLLPRI)
        rv |= APR_POLLPRI;
    if (event & POLLOUT)
        rv |= APR_POLLOUT;
    if (event & POLLERR)
        rv |= APR_POLLERR;
    if (event & POLLHUP)
        rv |= APR_POLLHUP;
    if (event & POLLNVAL)
        rv |= APR_POLLNVAL;

    DBG(4, "exiting\n");
    return rv;
}