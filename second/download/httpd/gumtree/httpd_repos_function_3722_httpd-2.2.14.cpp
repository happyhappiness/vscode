static apr_status_t call_port_getn(int port, port_event_t list[], 
                                   unsigned int max, unsigned int *nget,
                                   apr_interval_time_t timeout)
{
    struct timespec tv, *tvptr;
    int ret;
    apr_status_t rv = APR_SUCCESS;

    if (timeout < 0) {
        tvptr = NULL;
    }
    else {
        tv.tv_sec = (long) apr_time_sec(timeout);
        tv.tv_nsec = (long) apr_time_usec(timeout) * 1000;
        tvptr = &tv;
    }

    ret = port_getn(port, list, max, nget, tvptr);

    if (ret < 0) {
        rv = apr_get_netos_error();

        switch(rv) {
        case EINTR:
        case ETIME:
            if (*nget > 0) {
                /* This confusing API can return an event at the same time
                 * that it reports EINTR or ETIME.  If that occurs, just
                 * report the event.
                 * (Maybe it will be simplified; see thread
                 *   http://mail.opensolaris.org
                 *   /pipermail/networking-discuss/2009-August/011979.html
                 *  This code will still work afterwards.)
                 */
                rv = APR_SUCCESS;
                break;
            }
            if (rv == ETIME) {
                rv = APR_TIMEUP;
            }
        /* fall-through */
        default:
            *nget = 0;
        }
    }
    else if (*nget == 0) {
        rv = APR_TIMEUP;
    }

    return rv;
}