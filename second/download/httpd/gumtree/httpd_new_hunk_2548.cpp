    /*
     * make sure the expired records are omitted
     */
    now = apr_time_now();
    if ((rv = apr_dbm_open(&dbm, ctx->data_file, APR_DBM_RWCREATE,
                           DBM_FILE_MODE, ctx->pool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00815)
                     "Cannot open socache DBM file `%s' for "
                     "iterating", ctx->data_file);
        return rv;
    }
    rv = apr_dbm_firstkey(dbm, &dbmkey);
    while (rv == APR_SUCCESS && dbmkey.dptr != NULL) {
