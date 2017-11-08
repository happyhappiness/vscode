static int simple_setup_pollcb(simple_core_t * sc)
{
    int i;
    apr_status_t rv;
    int good_methods[] = {APR_POLLSET_KQUEUE, APR_POLLSET_PORT, APR_POLLSET_EPOLL};

    for (i = 0; i < sizeof(good_methods) / sizeof(void*); i++) {
        /* pqXXXXX: make size of pollcb configrable or dynamic */
        rv = apr_pollcb_create_ex(&sc->pollcb, 512,
                                  sc->pool, APR_POLLSET_NODEFAULT, good_methods[i]);
        if (!rv) {
            break;
        }
    }
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                   "simple_setup_pollcb: apr_pollcb_create failed for all possible backends!");
        return rv;
    }
    return rv;
}