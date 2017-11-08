void ssl_scache_shmcb_status(request_rec *r, int flags, apr_pool_t *p)
{
    server_rec *s = r->server;
    SSLModConfigRec *mc = myModConfig(s);
    void *shm_segment = apr_shm_baseaddr_get(mc->pSessionCacheDataMM);
    SHMCBHeader *header = shm_segment;
    unsigned int loop, total = 0, cache_total = 0, non_empty_subcaches = 0;
    time_t idx_expiry, min_expiry = 0, max_expiry = 0, average_expiry = 0;
    time_t now = time(NULL);
    double expiry_total = 0;
    int index_pct, cache_pct;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "inside shmcb_status");
    /* Perform the iteration inside the mutex to avoid corruption or invalid
     * pointer arithmetic. The rest of our logic uses read-only header data so
     * doesn't need the lock. */
    ssl_mutex_on(s);
    /* Iterate over the subcaches */
    for (loop = 0; loop < header->subcache_num; loop++) {
        SHMCBSubcache *subcache = SHMCB_SUBCACHE(header, loop);
        shmcb_subcache_expire(s, header, subcache);
        total += subcache->idx_used;
        cache_total += subcache->data_used;
        if (subcache->idx_used) {
            SHMCBIndex *idx = SHMCB_INDEX(subcache, subcache->idx_pos);
            non_empty_subcaches++;
            idx_expiry = idx->expires;
            expiry_total += (double)idx_expiry;
            max_expiry = ((idx_expiry > max_expiry) ? idx_expiry : max_expiry);
            if (!min_expiry)
                min_expiry = idx_expiry;
            else
                min_expiry = ((idx_expiry < min_expiry) ? idx_expiry : min_expiry);
        }
    }
    ssl_mutex_off(s);
    index_pct = (100 * total) / (header->index_num *
                                 header->subcache_num);
    cache_pct = (100 * cache_total) / (header->subcache_data_size *
                                       header->subcache_num);
    /* Generate HTML */
    ap_rprintf(r, "cache type: <b>SHMCB</b>, shared memory: <b>%d</b> "
               "bytes, current sessions: <b>%d</b><br>",
               mc->nSessionCacheDataSize, total);
    ap_rprintf(r, "subcaches: <b>%d</b>, indexes per subcache: <b>%d</b><br>",
               header->subcache_num, header->index_num);
    if (non_empty_subcaches) {
        average_expiry = (time_t)(expiry_total / (double)non_empty_subcaches);
        ap_rprintf(r, "time left on oldest entries' SSL sessions: ");
        if (now < average_expiry)
            ap_rprintf(r, "avg: <b>%d</b> seconds, (range: %d...%d)<br>",
                       (int)(average_expiry - now),
                       (int)(min_expiry - now),
                       (int)(max_expiry - now));
        else
            ap_rprintf(r, "expiry_threshold: <b>Calculation error!</b><br>");
    }

    ap_rprintf(r, "index usage: <b>%d%%</b>, cache usage: <b>%d%%</b><br>",
               index_pct, cache_pct);
    ap_rprintf(r, "total sessions stored since starting: <b>%lu</b><br>",
               header->stat_stores);
    ap_rprintf(r, "total sessions expired since starting: <b>%lu</b><br>",
               header->stat_expiries);
    ap_rprintf(r, "total (pre-expiry) sessions scrolled out of the cache: "
               "<b>%lu</b><br>", header->stat_scrolled);
    ap_rprintf(r, "total retrieves since starting: <b>%lu</b> hit, "
               "<b>%lu</b> miss<br>", header->stat_retrieves_hit,
               header->stat_retrieves_miss);
    ap_rprintf(r, "total removes since starting: <b>%lu</b> hit, "
               "<b>%lu</b> miss<br>", header->stat_removes_hit,
               header->stat_removes_miss);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "leaving shmcb_status");
}