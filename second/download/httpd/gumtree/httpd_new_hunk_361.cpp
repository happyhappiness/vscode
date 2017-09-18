    dbmkey.dsize = idlen;

    /* and fetch it from the DBM file 
     * XXX: Should we open the dbm against r->pool so the cleanup will
     * do the apr_dbm_close? This would make the code a bit cleaner.
     */
    if ((rc = apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
	    APR_DBM_RWCREATE, SSL_DBM_FILE_MODE, mc->pPool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                     "Cannot open SSLSessionCache DBM file `%s' for reading "
                     "(fetch)",
                     mc->szSessionCacheDataFile);
        return NULL;
    }
    rc = apr_dbm_fetch(dbm, dbmkey, &dbmval);
    if (rc != APR_SUCCESS) {
        apr_dbm_close(dbm);
        return NULL;
