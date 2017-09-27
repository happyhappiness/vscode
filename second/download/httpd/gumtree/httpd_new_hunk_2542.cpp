
    /* and fetch it from the DBM file
     * XXX: Should we open the dbm against r->pool so the cleanup will
     * do the apr_dbm_close? This would make the code a bit cleaner.
     */
    apr_pool_clear(ctx->pool);
    if ((rc = apr_dbm_open(&dbm, ctx->data_file, APR_DBM_RWCREATE,
                           DBM_FILE_MODE, ctx->pool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rc, s, APLOGNO(00809)
                     "Cannot open socache DBM file `%s' for reading "
                     "(fetch)",
                     ctx->data_file);
        return rc;
    }
    rc = apr_dbm_fetch(dbm, dbmkey, &dbmval);
