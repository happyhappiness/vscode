static apr_status_t simple_setup_workers(simple_core_t * sc)
{
    apr_status_t rv;

    rv = apr_thread_pool_create(&sc->workers,
                                sc->procmgr.thread_count,
                                sc->procmgr.thread_count, sc->pool);

    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "simple_setup_workers: apr_thread_pool_create with %d threads failed",
                     sc->procmgr.thread_count);
        return rv;
    }

    return APR_SUCCESS;
}