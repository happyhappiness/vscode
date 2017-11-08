static apr_status_t dbd_setup_init(apr_pool_t *pool, server_rec *s)
{
    svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
    apr_status_t rv;

    /* dbd_setup in 2.2.3 and under was causing spurious error messages
     * when dbd isn't configured.  We can stop that with a quick check here
     * together with a similar check in ap_dbd_open (where being
     * unconfigured is a genuine error that must be reported).
     */
    if (svr->name == no_dbdriver) {
        return APR_SUCCESS;
    }

    if (!svr->persist) {
        return APR_SUCCESS;
    }

    rv = dbd_setup(pool, svr);
    if (rv == APR_SUCCESS) {
        return rv;
    }

    /* we failed, so create a mutex so that subsequent competing callers
     * to ap_dbd_open can serialize themselves while they retry
     */
    rv = apr_thread_mutex_create(&svr->mutex, APR_THREAD_MUTEX_DEFAULT, pool);
    if (rv != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
                      "DBD: Failed to create thread mutex");
    }
    return rv;
}