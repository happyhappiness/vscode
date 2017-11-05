void ssl_scache_dbm_status(server_rec *s, apr_pool_t *p, void (*func)(char *, void *), void *arg)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_dbm_t *dbm;
    apr_datum_t dbmkey;
    apr_datum_t dbmval;
    int nElem;
    int nSize;
    int nAverage;
    apr_status_t rv;

    nElem = 0;
    nSize = 0;
    ssl_mutex_on(s);
    /*
     * XXX - Check what pool is to be used - TBD
     */
    if ((rv = apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
	                       APR_DBM_RWCREATE, SSL_DBM_FILE_MODE,
                           mc->pPool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot open SSLSessionCache DBM file `%s' for status "
                     "retrival",
                     mc->szSessionCacheDataFile);
        ssl_mutex_off(s);
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
    ssl_mutex_off(s);
    if (nSize > 0 && nElem > 0)
        nAverage = nSize / nElem;
    else
        nAverage = 0;
    func(apr_psprintf(p, "cache type: <b>DBM</b>, maximum size: <b>unlimited</b><br>"), arg);
    func(apr_psprintf(p, "current sessions: <b>%d</b>, current size: <b>%d</b> bytes<br>", nElem, nSize), arg);
    func(apr_psprintf(p, "average session size: <b>%d</b> bytes<br>", nAverage), arg);
    return;
}