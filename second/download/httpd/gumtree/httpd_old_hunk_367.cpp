
    /* We've kludged our pointer into the other cache's member variable. */
    shm_segment = (void *) mc->tSessionCacheDataTable;
    ssl_mutex_on(s);
    if (!shmcb_store_session(s, shm_segment, id, idlen, pSession, timeout))
        /* in this cache engine, "stores" should never fail. */
        ssl_log(s, SSL_LOG_ERROR, "'shmcb' code was unable to store a "
                "session in the cache.");
    else {
        ssl_log(s, SSL_LOG_TRACE, "shmcb_store successful");
        to_return = TRUE;
    }
    ssl_mutex_off(s);
    return to_return;
}

