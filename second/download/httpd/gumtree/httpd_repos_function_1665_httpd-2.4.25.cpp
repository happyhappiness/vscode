static apr_status_t ap_watchdog_get_instance(ap_watchdog_t **watchdog,
                                             const char *name,
                                             int parent,
                                             int singleton,
                                             apr_pool_t *p)
{
    ap_watchdog_t *w;
    const char *pver = parent ? AP_WATCHDOG_PVERSION : AP_WATCHDOG_CVERSION;

    if (parent && mpm_is_forked != AP_MPMQ_NOT_SUPPORTED) {
        /* Parent threads are not supported for
         * forked mpm's
         */
        *watchdog = NULL;
        return APR_ENOTIMPL;
    }
    w = ap_lookup_provider(AP_WATCHDOG_PGROUP, name, pver);
    if (w) {
        *watchdog = w;
        return APR_SUCCESS;
    }
    w = apr_pcalloc(p, sizeof(ap_watchdog_t));
    w->name      = name;
    w->pool      = p;
    w->singleton = parent ? 0 : singleton;
    *watchdog    = w;
    return ap_register_provider(p, AP_WATCHDOG_PGROUP, name,
                                pver, *watchdog);
}