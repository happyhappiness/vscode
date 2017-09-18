
    /* We've kludged our pointer into the other cache's member variable. */
    shm_segment = (void *) mc->tSessionCacheDataTable;
    ssl_mutex_on(s);
    if (!shmcb_store_session(s, shm_segment, id, idlen, pSession, timeout))
        /* in this cache engine, "stores" should never fail. */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "'shmcb' code was unable to store a "
                     "session in the cache.");
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "shmcb_store successful");
        to_return = TRUE;
    }
    ssl_mutex_off(s);
    return to_return;
}

