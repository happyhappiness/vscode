static apr_status_t dbd_setup(apr_pool_t *pool, server_rec *s)
{
    svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
    apr_status_t rv = apr_reslist_create(&svr->dbpool, svr->nmin, svr->nkeep,
                                         svr->nmax, svr->exptime,
                                         dbd_construct, dbd_destruct,
                                         svr, pool);
    if (rv == APR_SUCCESS) {
        apr_pool_cleanup_register(pool, svr->dbpool,
                                  (void*)apr_reslist_destroy,
                                  apr_pool_cleanup_null);
    }
    else {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
                      "DBD Pool: failed to initialise");
    }
    return rv;
}