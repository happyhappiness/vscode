static apr_int16_t get_event(apr_int16_t event)
{
    DBG_BUFF
    apr_int16_t rv = 0;
    DBG(4, "entered\n");

    if (event & APR_POLLIN)
        rv |= POLLIN;
    if (event & APR_POLLPRI)
        rv |= POLLPRI;
    if (event & APR_POLLOUT)
        rv |= POLLOUT;
    if (event & APR_POLLERR)
        rv |= POLLERR;
    if (event & APR_POLLHUP)
        rv |= POLLHUP;
    if (event & APR_POLLNVAL)
        rv |= POLLNVAL;

    DBG(4, "exiting\n");
    return rv;
}