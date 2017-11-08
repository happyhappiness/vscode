void ssl_scache_dbm_status(request_rec *r, int flags, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(r->server);
    apr_dbm_t *dbm;
    apr_datum_t dbmkey;
    apr_datum_t dbmval;
    int nElem;
    int nSize;
    int nAverage;
    apr_status_t rv;

    nElem = 0;
    nSize = 0;
    ssl_mutex_on(r->server);
    /*
     * XXX - Check what pool is to be used - TBD
     */
    if ((rv = apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
                               APR_DBM_RWCREATE, SSL_DBM_FILE_MODE,
                           mc->pPool)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                     "Cannot open SSLSessionCache DBM file `%s' for status "
                     "retrival",
                     mc->szSessionCacheDataFile);
        ssl_mutex_off(r->server);
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
        nElem += 1;
        nSize += dbmval.dsize;
    }
    apr_dbm_close(dbm);
    ssl_mutex_off(r->server);
    if (nSize > 0 && nElem > 0)
        nAverage = nSize / nElem;
    else
        nAverage = 0;
    ap_rprintf(r, "cache type: <b>DBM</b>, maximum size: <b>unlimited</b><br>");
    ap_rprintf(r, "current sessions: <b>%d</b>, current size: <b>%d</b> bytes<br>", nElem, nSize);
    ap_rprintf(r, "average session size: <b>%d</b> bytes<br>", nAverage);
    return;
}