void ssl_scache_shmcb_status(request_rec *r, int flags, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(r->server);
    SHMCBHeader *header;
    SHMCBQueue queue;
    SHMCBCache cache;
    SHMCBIndex *idx;
    unsigned int loop, total, cache_total, non_empty_divisions;
    int index_pct, cache_pct;
    double expiry_total;
    time_t average_expiry, now, max_expiry, min_expiry, idxexpiry;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "inside shmcb_status");

    /* Get the header structure. */
    shmcb_get_header(mc->tSessionCacheDataTable, &header);
    total = cache_total = non_empty_divisions = 0;
    average_expiry = max_expiry = min_expiry = 0;
    expiry_total = 0;

    /* It may seem strange to grab "now" at this point, but in theory
     * we should never have a negative threshold but grabbing "now" after
     * the loop (which performs expiries) could allow that chance. */
    now = time(NULL);
    for (loop = 0; loop <= header->division_mask; loop++) {
        if (shmcb_get_division(header, &queue, &cache, loop)) {
            shmcb_expire_division(r->server, &queue, &cache);
            total += shmcb_get_safe_uint(queue.pos_count);
            cache_total += shmcb_get_safe_uint(cache.pos_count);
            if (shmcb_get_safe_uint(queue.pos_count) > 0) {
                idx = shmcb_get_index(&queue,
                                     shmcb_get_safe_uint(queue.first_pos));
                non_empty_divisions++;
                idxexpiry = shmcb_get_safe_time(&(idx->expires));
                expiry_total += (double) idxexpiry;
                max_expiry = (idxexpiry > max_expiry ? idxexpiry :
                              max_expiry);
                if (min_expiry == 0)
                    min_expiry = idxexpiry;
                else
                    min_expiry = (idxexpiry < min_expiry ? idxexpiry :
                                  min_expiry);
            }
        }
    }
    index_pct = (100 * total) / (header->index_num * (header->division_mask + 1));
    cache_pct = (100 * cache_total) / (header->cache_data_size * (header->division_mask + 1));
    ap_rprintf(r, "cache type: <b>SHMCB</b>, shared memory: <b>%d</b> "
               "bytes, current sessions: <b>%d</b><br>",
               mc->nSessionCacheDataSize, total);
    ap_rprintf(r, "sub-caches: <b>%d</b>, indexes per sub-cache: "
               "<b>%d</b><br>", (int) header->division_mask + 1,
               (int) header->index_num);
    if (non_empty_divisions != 0) {
        average_expiry = (time_t)(expiry_total / (double)non_empty_divisions);
        ap_rprintf(r, "time left on oldest entries' SSL sessions: ");
        if (now < average_expiry)
            ap_rprintf(r, "avg: <b>%d</b> seconds, (range: %d...%d)<br>",
                       (int)(average_expiry - now), (int) (min_expiry - now),
                       (int)(max_expiry - now));
        else
            ap_rprintf(r, "expiry threshold: <b>Calculation Error!</b>"
                       "<br>");

    }
    ap_rprintf(r, "index usage: <b>%d%%</b>, cache usage: <b>%d%%</b>"
               "<br>", index_pct, cache_pct);
    ap_rprintf(r, "total sessions stored since starting: <b>%lu</b><br>",
               header->num_stores);
    ap_rprintf(r, "total sessions expired since starting: <b>%lu</b><br>",
               header->num_expiries);
    ap_rprintf(r, "total (pre-expiry) sessions scrolled out of the "
               "cache: <b>%lu</b><br>", header->num_scrolled);
    ap_rprintf(r, "total retrieves since starting: <b>%lu</b> hit, "
               "<b>%lu</b> miss<br>", header->num_retrieves_hit,
               header->num_retrieves_miss);
    ap_rprintf(r, "total removes since starting: <b>%lu</b> hit, "
               "<b>%lu</b> miss<br>", header->num_removes_hit,
               header->num_removes_miss);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "leaving shmcb_status");
    return;
}