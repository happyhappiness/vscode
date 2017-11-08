void ssl_scache_dbm_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_dbm_t *dbm;
    apr_status_t rv;

    /* for the DBM we need the data file */
    if (mc->szSessionCacheDataFile == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "SSLSessionCache required");
        ssl_die();
    }

    /* open it once to create it and to make sure it _can_ be created */
    ssl_mutex_on(s);
    if ((rv = apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
            APR_DBM_RWCREATE, SSL_DBM_FILE_MODE, mc->pPool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot create SSLSessionCache DBM file `%s'",
                     mc->szSessionCacheDataFile);
        ssl_mutex_off(s);
        return;
    }
    apr_dbm_close(dbm);

#if !defined(OS2) && !defined(WIN32) && !defined(BEOS) && !defined(NETWARE)
    /*
     * We have to make sure the Apache child processes have access to
     * the DBM file. But because there are brain-dead platforms where we
     * cannot exactly determine the suffixes we try all possibilities.
     */
    if (geteuid() == 0 /* is superuser */) {
        chown(mc->szSessionCacheDataFile, unixd_config.user_id, -1 /* no gid change */);
        if (chown(apr_pstrcat(p, mc->szSessionCacheDataFile, SSL_DBM_FILE_SUFFIX_DIR, NULL),
                  unixd_config.user_id, -1) == -1) {
            if (chown(apr_pstrcat(p, mc->szSessionCacheDataFile, ".db", NULL),
                      unixd_config.user_id, -1) == -1)
                chown(apr_pstrcat(p, mc->szSessionCacheDataFile, ".dir", NULL),
                      unixd_config.user_id, -1);
        }
        if (chown(apr_pstrcat(p, mc->szSessionCacheDataFile, SSL_DBM_FILE_SUFFIX_PAG, NULL),
                  unixd_config.user_id, -1) == -1) {
            if (chown(apr_pstrcat(p, mc->szSessionCacheDataFile, ".db", NULL),
                      unixd_config.user_id, -1) == -1)
                chown(apr_pstrcat(p, mc->szSessionCacheDataFile, ".pag", NULL),
                      unixd_config.user_id, -1);
        }
    }
#endif
    ssl_mutex_off(s);
    ssl_scache_dbm_expire(s);
    return;
}