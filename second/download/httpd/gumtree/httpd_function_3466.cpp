static apr_status_t socache_dbm_remove(ap_socache_instance_t *ctx, 
                                       server_rec *s, const unsigned char *id,
                                       unsigned int idlen, apr_pool_t *p)
{
    apr_dbm_t *dbm;
    apr_datum_t dbmkey;
    apr_status_t rv;

    /* create DBM key and values */
    dbmkey.dptr  = (char *)id;
    dbmkey.dsize = idlen;

    /* and delete it from the DBM file */
    apr_pool_clear(ctx->pool);

    if ((rv = apr_dbm_open(&dbm, ctx->data_file, APR_DBM_RWCREATE, 
                           DBM_FILE_MODE, ctx->pool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot open socache DBM file `%s' for writing "
                     "(delete)",
                     ctx->data_file);
        return rv;
    }
    apr_dbm_delete(dbm, dbmkey);
    apr_dbm_close(dbm);

    return APR_SUCCESS;
}