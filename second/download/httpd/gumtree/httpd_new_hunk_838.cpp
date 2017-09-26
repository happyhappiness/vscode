}

BOOL ssl_scache_shmcb_store(server_rec *s, UCHAR *id, int idlen,
                           time_t timeout, SSL_SESSION * pSession)
{
    SSLModConfigRec *mc = myModConfig(s);
    BOOL to_return = FALSE;

    ssl_mutex_on(s);
    if (!shmcb_store_session(s, mc->tSessionCacheDataTable, id, idlen,
                             pSession, timeout))
        /* in this cache engine, "stores" should never fail. */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "'shmcb' code was unable to store a "
                     "session in the cache.");
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
