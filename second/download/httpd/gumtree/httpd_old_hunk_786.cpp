    return to_return;
}

SSL_SESSION *ssl_scache_shmcb_retrieve(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    void *shm_segment;
    SSL_SESSION *pSession;

    /* We've kludged our pointer into the other cache's member variable. */
    shm_segment = (void *) mc->tSessionCacheDataTable;
    ssl_mutex_on(s);
    pSession = shmcb_retrieve_session(s, shm_segment, id, idlen);
    ssl_mutex_off(s);
    if (pSession)
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "shmcb_retrieve had a hit");
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
