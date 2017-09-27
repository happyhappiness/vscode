    return pSession;
}

void ssl_scache_shmcb_remove(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    void *shm_segment;

    /* We've kludged our pointer into the other cache's member variable. */
    shm_segment = (void *) mc->tSessionCacheDataTable;
    ssl_mutex_on(s);
    shmcb_remove_session(s, shm_segment, id, idlen);
    ssl_mutex_off(s);
}

void ssl_scache_shmcb_expire(server_rec *s)
{
    /* NOP */
    return;
}

void ssl_scache_shmcb_status(server_rec *s, apr_pool_t *p,
                            void (*func) (char *, void *), void *arg)
{
    SSLModConfigRec *mc = myModConfig(s);
    SHMCBHeader *header;
    SHMCBQueue queue;
    SHMCBCache cache;
    SHMCBIndex *idx;
    void *shm_segment;
    unsigned int loop, total, cache_total, non_empty_divisions;
    int index_pct, cache_pct;
    double expiry_total;
    time_t average_expiry, now, max_expiry, min_expiry, idxexpiry;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, 
                 "inside ssl_scache_shmcb_status");

    /* We've kludged our pointer into the other cache's member variable. */
    shm_segment = (void *) mc->tSessionCacheDataTable;

    /* Get the header structure. */
    shmcb_get_header(shm_segment, &header);
    total = cache_total = non_empty_divisions = 0;
    average_expiry = max_expiry = min_expiry = 0;
    expiry_total = 0;

    /* It may seem strange to grab "now" at this point, but in theory
     * we should never have a negative threshold but grabbing "now" after
     * the loop (which performs expiries) could allow that chance. */
    now = time(NULL);
    for (loop = 0; loop <= header->division_mask; loop++) {
        if (shmcb_get_division(header, &queue, &cache, loop)) {
            shmcb_expire_division(s, &queue, &cache);
            total += shmcb_get_safe_uint(queue.pos_count);
            cache_total += shmcb_get_safe_uint(cache.pos_count);
            if (shmcb_get_safe_uint(queue.pos_count) > 0) {
                idx = shmcb_get_index(&queue,
                                     shmcb_get_safe_uint(queue.first_pos));
                non_empty_divisions++;
