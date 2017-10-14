static apr_status_t dbd_setup(apr_pool_t *pool, svr_cfg *svr)
{
    apr_status_t rv;

    /* create a pool just for the reslist from a process-lifetime pool;
     * that pool (s->process->pool in the dbd_setup_lock case,
     * whatever was passed to ap_run_child_init in the dbd_setup_init case)
     * will be shared with other threads doing other non-mod_dbd things
     * so we can't use it for the reslist directly
     */
    rv = apr_pool_create(&svr->pool, pool);
    if (rv != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
                      "DBD: Failed to create reslist memory pool");
        return rv;
    }

    rv = apr_reslist_create(&svr->dbpool, svr->nmin, svr->nkeep, svr->nmax,
                            apr_time_from_sec(svr->exptime),
                            dbd_construct, dbd_destruct, svr, svr->pool);
    if (rv == APR_SUCCESS) {
        apr_pool_cleanup_register(svr->pool, svr->dbpool,
                                  (void*)apr_reslist_destroy,
                                  apr_pool_cleanup_null);
    }
    else {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, svr->pool,
                      "DBD: failed to initialise");
        apr_pool_destroy(svr->pool);
        svr->pool = NULL;
    }

    return rv;
}