void ssl_scache_dbm_expire(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);
    SSLSrvConfigRec *sc = mySrvConfig(s);
    static time_t tLast = 0;
    apr_dbm_t *dbm;
    apr_datum_t dbmkey;
    apr_datum_t dbmval;
    apr_pool_t *p;
    time_t tExpiresAt;
    int nElements = 0;
    int nDeleted = 0;
    int bDelete;
    apr_datum_t *keylist;
    int keyidx;
    int i;
    time_t tNow;
    apr_status_t rv;

    /*
     * make sure the expiration for still not-accessed session
     * cache entries is done only from time to time
     */
    tNow = time(NULL);
    if (tNow < tLast+sc->session_cache_timeout)
        return;
    tLast = tNow;

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

    ssl_mutex_on(s);
    for (;;) {
        /* allocate the key array in a memory sub pool */
        apr_pool_sub_make(&p, mc->pPool, NULL);
        if (p == NULL)
            break;
        if ((keylist = apr_palloc(p, sizeof(dbmkey)*KEYMAX)) == NULL) {
            apr_pool_destroy(p);
            break;
        }

        /* pass 1: scan DBM database */
        keyidx = 0;
        if ((rv = apr_dbm_open(&dbm, mc->szSessionCacheDataFile, 
                               APR_DBM_RWCREATE,SSL_DBM_FILE_MODE,
                               p)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot open SSLSessionCache DBM file `%s' for "
                         "scanning",
                         mc->szSessionCacheDataFile);
            apr_pool_destroy(p);
            break;
        }
        apr_dbm_firstkey(dbm, &dbmkey);
        while (dbmkey.dptr != NULL) {
            nElements++;
            bDelete = FALSE;
            apr_dbm_fetch(dbm, dbmkey, &dbmval);
            if (dbmval.dsize <= sizeof(time_t) || dbmval.dptr == NULL)
                bDelete = TRUE;
            else {
                memcpy(&tExpiresAt, dbmval.dptr, sizeof(time_t));
                if (tExpiresAt <= tNow)
                    bDelete = TRUE;
            }
            if (bDelete) {
                if ((keylist[keyidx].dptr = apr_palloc(p, dbmkey.dsize)) != NULL) {
                    memcpy(keylist[keyidx].dptr, dbmkey.dptr, dbmkey.dsize);
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
        if (apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
		APR_DBM_RWCREATE,SSL_DBM_FILE_MODE, p) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot re-open SSLSessionCache DBM file `%s' for "
                         "expiring",
                         mc->szSessionCacheDataFile);
            apr_pool_destroy(p);
            break;
        }
        for (i = 0; i < keyidx; i++) {
            apr_dbm_delete(dbm, keylist[i]);
            nDeleted++;
        }
        apr_dbm_close(dbm);

        /* destroy temporary pool */
        apr_pool_destroy(p);

        if (keyidx < KEYMAX)
            break;
    }
    ssl_mutex_off(s);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Inter-Process Session Cache (DBM) Expiry: "
                 "old: %d, new: %d, removed: %d",
                 nElements, nElements-nDeleted, nDeleted);
    return;
}