
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

