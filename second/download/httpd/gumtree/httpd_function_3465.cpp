static apr_status_t socache_dbm_retrieve(ap_socache_instance_t *ctx, server_rec *s, 
                                         const unsigned char *id, unsigned int idlen,
                                         unsigned char *dest, unsigned int *destlen,
                                         apr_pool_t *p)
{
    apr_dbm_t *dbm;
    apr_datum_t dbmkey;
    apr_datum_t dbmval;
    unsigned int nData;
    apr_time_t expiry;
    apr_time_t now;
    apr_status_t rc;

    /* allow the regular expiring to occur */
    socache_dbm_expire(ctx, s);

    /* create DBM key and values */
    dbmkey.dptr  = (char *)id;
    dbmkey.dsize = idlen;

    /* and fetch it from the DBM file
     * XXX: Should we open the dbm against r->pool so the cleanup will
     * do the apr_dbm_close? This would make the code a bit cleaner.
     */
    apr_pool_clear(ctx->pool);
    if ((rc = apr_dbm_open(&dbm, ctx->data_file, APR_DBM_RWCREATE, 
                           DBM_FILE_MODE, ctx->pool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                     "Cannot open socache DBM file `%s' for reading "
                     "(fetch)",
                     ctx->data_file);
        return rc;
    }
    rc = apr_dbm_fetch(dbm, dbmkey, &dbmval);
    if (rc != APR_SUCCESS) {
        apr_dbm_close(dbm);
        return APR_NOTFOUND;
    }
    if (dbmval.dptr == NULL || dbmval.dsize <= sizeof(apr_time_t)) {
        apr_dbm_close(dbm);
        return APR_EGENERAL;
    }

    /* parse resulting data */
    nData = dbmval.dsize-sizeof(apr_time_t);
    if (nData > *destlen) {
        apr_dbm_close(dbm);
        return APR_ENOSPC;
    }    

    *destlen = nData;
    memcpy(&expiry, dbmval.dptr, sizeof(apr_time_t));
    memcpy(dest, (char *)dbmval.dptr + sizeof(apr_time_t), nData);

    apr_dbm_close(dbm);

    /* make sure the stuff is still not expired */
    now = apr_time_now();
    if (expiry <= now) {
        socache_dbm_remove(ctx, s, id, idlen, p);
        return APR_NOTFOUND;
    }

    return APR_SUCCESS;
}