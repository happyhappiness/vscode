SSL_SESSION *ssl_scache_dbm_retrieve(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_dbm_t *dbm;
    apr_datum_t dbmkey;
    apr_datum_t dbmval;
    SSL_SESSION *sess = NULL;
    MODSSL_D2I_SSL_SESSION_CONST unsigned char *ucpData;
    int nData;
    time_t expiry;
    time_t now;
    apr_status_t rc;

    /* allow the regular expiring to occur */
    ssl_scache_dbm_expire(s);

    /* create DBM key and values */
    dbmkey.dptr  = (char *)id;
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
    ucpData = malloc(nData);
    if (ucpData == NULL) {
        apr_dbm_close(dbm);
        ssl_mutex_off(s);
        return NULL;
    }
    /* Cast needed, ucpData may be const */
    memcpy((unsigned char *)ucpData,
           (char *)dbmval.dptr + sizeof(time_t), nData);
    memcpy(&expiry, dbmval.dptr, sizeof(time_t));

    apr_dbm_close(dbm);
    ssl_mutex_off(s);

    /* make sure the stuff is still not expired */
    now = time(NULL);
    if (expiry <= now) {
        ssl_scache_dbm_remove(s, id, idlen);
        return NULL;
    }

    /* unstreamed SSL_SESSION */
    sess = d2i_SSL_SESSION(NULL, &ucpData, nData);

    return sess;
}