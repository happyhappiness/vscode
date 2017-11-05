static apr_status_t dbd_setup(server_rec *s, dbd_group_t *group)
{
    dbd_cfg_t *cfg = group->cfg;
    apr_status_t rv;

    /* We create the reslist using a sub-pool of the pool passed to our
     * child_init hook.  No other threads can be here because we're
     * either in the child_init phase or dbd_setup_lock() acquired our mutex.
     * No other threads will use this sub-pool after this, except via
     * reslist calls, which have an internal mutex.
     *
     * We need to short-circuit the cleanup registered internally by
     * apr_reslist_create().  We do this by registering dbd_destroy()
     * as a cleanup afterwards, so that it will run before the reslist's
     * internal cleanup.
     *
     * If we didn't do this, then we could free memory twice when the pool
     * was destroyed.  When apr_pool_destroy() runs, it first destroys all
     * all the per-connection sub-pools created in dbd_construct(), and
     * then it runs the reslist's cleanup.  The cleanup calls dbd_destruct()
     * on each resource, which would then attempt to destroy the sub-pools
     * a second time.
     */
    rv = apr_reslist_create(&group->reslist,
                            cfg->nmin, cfg->nkeep, cfg->nmax,
                            apr_time_from_sec(cfg->exptime),
                            dbd_construct, dbd_destruct, group,
                            group->pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "DBD: failed to initialise");
        return rv;
    }

    apr_pool_cleanup_register(group->pool, group, dbd_destroy,
                              apr_pool_cleanup_null);

    return APR_SUCCESS;
}