    dbmkey.dsize = idlen;

    /* and fetch it from the DBM file 
     * XXX: Should we open the dbm against r->pool so the cleanup will
     * do the apr_dbm_close? This would make the code a bit cleaner.
     */
    ssl_mutex_on(s);
    if ((rc = apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
	    APR_DBM_RWCREATE, SSL_DBM_FILE_MODE, mc->pPool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                     "Cannot open SSLSessionCache DBM file `%s' for reading "
                     "(fetch)",
                     mc->szSessionCacheDataFile);
        ssl_mutex_off(s);
        return NULL;
    }
    rc = apr_dbm_fetch(dbm, dbmkey, &dbmval);
    if (rc != APR_SUCCESS) {
        apr_dbm_close(dbm);
        ssl_mutex_off(s);
        return NULL;
    }
    if (dbmval.dptr == NULL || dbmval.dsize <= sizeof(time_t)) {
        apr_dbm_close(dbm);
        ssl_mutex_off(s);
        return NULL;
    }

    /* parse resulting data */
    nData = dbmval.dsize-sizeof(time_t);
    ucpData = (UCHAR *)malloc(nData);
    if (ucpData == NULL) {
        apr_dbm_close(dbm);
        ssl_mutex_off(s);
        return NULL;
    }
    memcpy(ucpData, (char *)dbmval.dptr+sizeof(time_t), nData);
    memcpy(&expiry, dbmval.dptr, sizeof(time_t));

    apr_dbm_close(dbm);
    ssl_mutex_off(s);

    /* make sure the stuff is still not expired */
    now = time(NULL);
    if (expiry <= now) {
        ssl_scache_dbm_remove(s, id, idlen);
        return NULL;
