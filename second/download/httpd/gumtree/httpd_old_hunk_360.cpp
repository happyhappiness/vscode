        return FALSE;
    memcpy((char *)dbmval.dptr, &expiry, sizeof(time_t));
    memcpy((char *)dbmval.dptr+sizeof(time_t), ucaData, nData);

    /* and store it to the DBM file */
    ssl_mutex_on(s);
    if (apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
	    APR_DBM_RWCREATE, SSL_DBM_FILE_MODE, mc->pPool) != APR_SUCCESS) {
        ssl_log(s, SSL_LOG_ERROR|SSL_ADD_ERRNO,
                "Cannot open SSLSessionCache DBM file `%s' for writing (store)",
                mc->szSessionCacheDataFile);
        ssl_mutex_off(s);
        free(dbmval.dptr);
        return FALSE;
    }
    if (apr_dbm_store(dbm, dbmkey, dbmval) != APR_SUCCESS) {
        ssl_log(s, SSL_LOG_ERROR|SSL_ADD_ERRNO,
                "Cannot store SSL session to DBM file `%s'",
                mc->szSessionCacheDataFile);
        apr_dbm_close(dbm);
        ssl_mutex_off(s);
        free(dbmval.dptr);
        return FALSE;
    }
    apr_dbm_close(dbm);
