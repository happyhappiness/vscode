SSL_SESSION *ssl_scache_shmcb_retrieve(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    SSL_SESSION *pSession;

    ssl_mutex_on(s);
    pSession = shmcb_retrieve_session(s, mc->tSessionCacheDataTable, id, idlen);
    ssl_mutex_off(s);
    if (pSession)
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "shmcb_retrieve had a hit");
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "shmcb_retrieve had a miss");
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                     "Client requested a 'session-resume' but "
                     "we have no such session.");
    }
    return pSession;
}