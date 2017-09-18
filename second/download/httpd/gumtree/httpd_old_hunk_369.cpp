    void *shm_segment;
    unsigned int loop, total, cache_total, non_empty_divisions;
    int index_pct, cache_pct;
    double expiry_total;
    time_t average_expiry, now, max_expiry, min_expiry, idxexpiry;

    ssl_log(s, SSL_LOG_TRACE, "inside ssl_scache_shmcb_status");

    /* We've kludged our pointer into the other cache's member variable. */
    shm_segment = (void *) mc->tSessionCacheDataTable;

    /* Get the header structure. */
    shmcb_get_header(shm_segment, &header);
