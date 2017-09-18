    /* We've kludged our pointer into the other cache's member variable. */
    shm_segment = (void *) mc->tSessionCacheDataTable;
    ssl_mutex_on(s);
    pSession = shmcb_retrieve_session(s, shm_segment, id, idlen);
    ssl_mutex_off(s);
    if (pSession)
        ssl_log(s, SSL_LOG_TRACE, "shmcb_retrieve had a hit");
    else {
        ssl_log(s, SSL_LOG_TRACE, "shmcb_retrieve had a miss");
        ssl_log(s, SSL_LOG_INFO, "Client requested a 'session-resume' but "
                "we have no such session.");
    }
    return pSession;
}

void ssl_scache_shmcb_remove(server_rec *s, UCHAR *id, int idlen)
{
