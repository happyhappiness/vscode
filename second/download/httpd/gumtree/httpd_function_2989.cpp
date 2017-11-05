static void socache_dbm_expire(ap_socache_instance_t *ctx, server_rec *s)
{
    apr_dbm_t *dbm;
    apr_datum_t dbmkey;
    apr_datum_t dbmval;
    apr_time_t expiry;
    int elts = 0;
    int deleted = 0;
    int expired;
    apr_datum_t *keylist;
    int keyidx;
    int i;
    apr_time_t now;
    apr_status_t rv;

    /*
     * make sure the expiration for still not-accessed
     * socache entries is done only from time to time
     */
    now = apr_time_now();

    if (now < ctx->last_expiry + ctx->expiry_interval) {
        return;
    }

    ctx->last_expiry = now;

    /*
     * Here we have to be very carefully: Not all DBM libraries are
     * smart enough to allow one to iterate over the elements and at the
     * same time delete expired ones. Some of them get totally crazy
     * while others have no problems. So we have to do it the slower but
     * more safe way: we first iterate over all elements and remember
     * those which have to be expired. Then in a second pass we delete
     * all those expired elements. Additionally we reopen the DBM file
     * to be really safe in state.
     */

#define KEYMAX 1024

    for (;;) {
        /* allocate the key array in a memory sub pool */
        apr_pool_clear(ctx->pool);

        if ((keylist = apr_palloc(ctx->pool, sizeof(dbmkey)*KEYMAX)) == NULL) {
            break;
        }

        /* pass 1: scan DBM database */
        keyidx = 0;
        if ((rv = apr_dbm_open(&dbm, ctx->data_file, APR_DBM_RWCREATE,
                               DBM_FILE_MODE, ctx->pool)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot open socache DBM file `%s' for "
                         "scanning",
                         ctx->data_file);
            break;
        }
        apr_dbm_firstkey(dbm, &dbmkey);
        while (dbmkey.dptr != NULL) {
            elts++;
            expired = FALSE;
            apr_dbm_fetch(dbm, dbmkey, &dbmval);
            if (dbmval.dsize <= sizeof(apr_time_t) || dbmval.dptr == NULL)
                expired = TRUE;
            else {
                memcpy(&expiry, dbmval.dptr, sizeof(apr_time_t));
                if (expiry <= now)
                    expired = TRUE;
            }
            if (expired) {
                if ((keylist[keyidx].dptr = apr_pmemdup(ctx->pool, dbmkey.dptr, dbmkey.dsize)) != NULL) {
                    keylist[keyidx].dsize = dbmkey.dsize;
                    keyidx++;
                    if (keyidx == KEYMAX)
                        break;
                }
            }
            apr_dbm_nextkey(dbm, &dbmkey);
        }
        apr_dbm_close(dbm);

        /* pass 2: delete expired elements */
        if (apr_dbm_open(&dbm, ctx->data_file, APR_DBM_RWCREATE,
                         DBM_FILE_MODE, ctx->pool) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot re-open socache DBM file `%s' for "
                         "expiring",
                         ctx->data_file);
            break;
        }
        for (i = 0; i < keyidx; i++) {
            apr_dbm_delete(dbm, keylist[i]);
            deleted++;
        }
        apr_dbm_close(dbm);

        if (keyidx < KEYMAX)
            break;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "DBM socache expiry: "
                 "old: %d, new: %d, removed: %d",
                 elts, elts-deleted, deleted);
}