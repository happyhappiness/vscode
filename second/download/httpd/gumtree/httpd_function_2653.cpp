static apr_status_t dbd_construct(void **data_ptr,
                                  void *params, apr_pool_t *pool)
{
    dbd_group_t *group = params;
    dbd_cfg_t *cfg = group->cfg;
    apr_pool_t *rec_pool, *prepared_pool;
    ap_dbd_t *rec;
    apr_status_t rv;

    rv = apr_pool_create(&rec_pool, pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, cfg->server,
                     "DBD: Failed to create memory pool");
        return rv;
    }

    rec = apr_pcalloc(rec_pool, sizeof(ap_dbd_t));

    rec->pool = rec_pool;

    /* The driver is loaded at config time now, so this just checks a hash.
     * If that changes, the driver DSO could be registered to unload against
     * our pool, which is probably not what we want.  Error checking isn't
     * necessary now, but in case that changes in the future ...
     */
    rv = apr_dbd_get_driver(rec->pool, cfg->name, &rec->driver);
    if (rv != APR_SUCCESS) {
        switch (rv) {
        case APR_ENOTIMPL:
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
                         "DBD: driver for %s not available", cfg->name);
            break;
        case APR_EDSOOPEN:
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
                         "DBD: can't find driver for %s", cfg->name);
            break;
        case APR_ESYMNOTFOUND:
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
                         "DBD: driver for %s is invalid or corrupted",
                         cfg->name);
            break;
        default:
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
                         "DBD: mod_dbd not compatible with APR in get_driver");
            break;
        }

        apr_pool_destroy(rec->pool);
        return rv;
    }

    rv = apr_dbd_open(rec->driver, rec->pool, cfg->params, &rec->handle);
    if (rv != APR_SUCCESS) {
        switch (rv) {
        case APR_EGENERAL:
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
                         "DBD: Can't connect to %s", cfg->name);
            break;
        default:
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
                         "DBD: mod_dbd not compatible with APR in open");
            break;
        }

        apr_pool_destroy(rec->pool);
        return rv;
    }

    apr_pool_cleanup_register(rec->pool, rec, dbd_close,
                              apr_pool_cleanup_null);

    /* we use a sub-pool for the prepared statements for each connection so
     * that they will be cleaned up first, before the connection is closed
     */
    rv = apr_pool_create(&prepared_pool, rec->pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, cfg->server,
                     "DBD: Failed to create memory pool");

        apr_pool_destroy(rec->pool);
        return rv;
    }

    rv = dbd_prepared_init(prepared_pool, cfg, rec);
    if (rv != APR_SUCCESS) {
        const char *errmsg = apr_dbd_error(rec->driver, rec->handle, rv);
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
                     "DBD: failed to prepare SQL statements: %s",
                     (errmsg ? errmsg : "[???]"));

        apr_pool_destroy(rec->pool);
        return rv;
    }

    *data_ptr = rec;

    return APR_SUCCESS;
}