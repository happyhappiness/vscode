
        if (keyidx < KEYMAX)
            break;
    }
    ssl_mutex_off(s);

    ssl_log(s, SSL_LOG_TRACE, "Inter-Process Session Cache (DBM) Expiry: "
            "old: %d, new: %d, removed: %d", nElements, nElements-nDeleted, nDeleted);
    return;
}

void ssl_scache_dbm_status(server_rec *s, apr_pool_t *p, void (*func)(char *, void *), void *arg)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_dbm_t *dbm;
    apr_datum_t dbmkey;
    apr_datum_t dbmval;
    int nElem;
    int nSize;
    int nAverage;

    nElem = 0;
    nSize = 0;
    ssl_mutex_on(s);
    /*
     * XXX - Check what pool is to be used - TBD
     */
    if (apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
	                 APR_DBM_RWCREATE, SSL_DBM_FILE_MODE, mc->pPool) != APR_SUCCESS) {
        ssl_log(s, SSL_LOG_ERROR|SSL_ADD_ERRNO,
                "Cannot open SSLSessionCache DBM file `%s' for status retrival",
                mc->szSessionCacheDataFile);
        ssl_mutex_off(s);
        return;
    }
    /*
     * XXX - Check the return value of apr_dbm_firstkey, apr_dbm_fetch - TBD
     */
