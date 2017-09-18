
void ssl_scache_dbm_remove(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_dbm_t *dbm;
    apr_datum_t dbmkey;
    apr_status_t rv;

    /* create DBM key and values */
    dbmkey.dptr  = (char *)id;
    dbmkey.dsize = idlen;

    /* and delete it from the DBM file */
    ssl_mutex_on(s);
    if ((rv = apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
	    APR_DBM_RWCREATE, SSL_DBM_FILE_MODE, mc->pPool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot open SSLSessionCache DBM file `%s' for writing "
                     "(delete)",
                     mc->szSessionCacheDataFile);
        ssl_mutex_off(s);
        return;
    }
    apr_dbm_delete(dbm, dbmkey);
    apr_dbm_close(dbm);
    ssl_mutex_off(s);
