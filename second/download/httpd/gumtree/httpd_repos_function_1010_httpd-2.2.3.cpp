static apr_status_t dbd_setup_lock(apr_pool_t *pool, server_rec *s)
{
    svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
    apr_status_t rv, rv2 = APR_SUCCESS;

    /* several threads could be here at the same time, all trying to
     * initialize the reslist because dbd_setup_init failed to do so
     */
    if (!svr->mutex) {
        /* we already logged an error when the mutex couldn't be created */
        return APR_EGENERAL;
    }

    rv = apr_thread_mutex_lock(svr->mutex);
    if (rv != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
                      "DBD: Failed to acquire thread mutex");
        return rv;
    }

    if (!svr->dbpool) {
        rv2 = dbd_setup(s->process->pool, svr);
    }

    rv = apr_thread_mutex_unlock(svr->mutex);
    if (rv != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
                      "DBD: Failed to release thread mutex");
        if (rv2 == APR_SUCCESS) {
            rv2 = rv;
        }
    }
    return rv2;
}