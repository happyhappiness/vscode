static void socache_dbm_status(ap_socache_instance_t *ctx, request_rec *r,
                               int flags)
{
    apr_dbm_t *dbm;
    apr_datum_t dbmkey;
    apr_datum_t dbmval;
    int elts;
    long size;
    int avg;
    apr_status_t rv;

    elts = 0;
    size = 0;

    apr_pool_clear(ctx->pool);
    if ((rv = apr_dbm_open(&dbm, ctx->data_file, APR_DBM_RWCREATE,
                           DBM_FILE_MODE, ctx->pool)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00814)
                     "Cannot open socache DBM file `%s' for status "
                     "retrival",
                     ctx->data_file);
        return;
    }
    /*
     * XXX - Check the return value of apr_dbm_firstkey, apr_dbm_fetch - TBD
     */
    apr_dbm_firstkey(dbm, &dbmkey);
    for ( ; dbmkey.dptr != NULL; apr_dbm_nextkey(dbm, &dbmkey)) {
        apr_dbm_fetch(dbm, dbmkey, &dbmval);
        if (dbmval.dptr == NULL)
            continue;
        elts += 1;
        size += dbmval.dsize;
    }
    apr_dbm_close(dbm);
    if (size > 0 && elts > 0)
        avg = (int)(size / (long)elts);
    else
        avg = 0;
    if (!(flags & AP_STATUS_SHORT)) {
        ap_rprintf(r, "cache type: <b>DBM</b>, maximum size: <b>unlimited</b><br>");
        ap_rprintf(r, "current entries: <b>%d</b>, current size: <b>%ld</b> bytes<br>", elts, size);
        ap_rprintf(r, "average entry size: <b>%d</b> bytes<br>", avg);
    }
    else {
        ap_rputs("CacheType: DBM\n", r);
        ap_rputs("CacheMaximumSize: unlimited\n", r);
        ap_rprintf(r, "CacheCurrentEntries: %d\n", elts);
        ap_rprintf(r, "CacheCurrentSize: %ld\n", size);
        ap_rprintf(r, "CacheAvgEntrySize: %d\n", avg);
    }
    return;
}