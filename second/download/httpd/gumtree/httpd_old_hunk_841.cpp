                                  min_expiry);
            }
        }
    }
    index_pct = (100 * total) / (header->index_num * (header->division_mask + 1));
    cache_pct = (100 * cache_total) / (header->cache_data_size * (header->division_mask + 1));
    func(apr_psprintf(p, "cache type: <b>SHMCB</b>, shared memory: <b>%d</b> "
                     "bytes, current sessions: <b>%d</b><br>",
                     mc->nSessionCacheDataSize, total), arg);
    func(apr_psprintf(p, "sub-caches: <b>%d</b>, indexes per sub-cache: "
                     "<b>%d</b><br>", (int) header->division_mask + 1,
                     (int) header->index_num), arg);
    if (non_empty_divisions != 0) {
        average_expiry = (time_t)(expiry_total / (double)non_empty_divisions);
        func(apr_psprintf(p, "time left on oldest entries' SSL sessions: "), arg);
        if (now < average_expiry)
            func(apr_psprintf(p, "avg: <b>%d</b> seconds, (range: %d...%d)<br>",
                            (int)(average_expiry - now), (int) (min_expiry - now),
                            (int)(max_expiry - now)), arg);
        else
            func(apr_psprintf(p, "expiry threshold: <b>Calculation Error!</b>" 
                             "<br>"), arg);

    }
    func(apr_psprintf(p, "index usage: <b>%d%%</b>, cache usage: <b>%d%%</b>"
                     "<br>", index_pct, cache_pct), arg);
    func(apr_psprintf(p, "total sessions stored since starting: <b>%lu</b><br>",
                     header->num_stores), arg);
    func(apr_psprintf(p,"total sessions expired since starting: <b>%lu</b><br>",
                     header->num_expiries), arg);
    func(apr_psprintf(p, "total (pre-expiry) sessions scrolled out of the "
                     "cache: <b>%lu</b><br>", header->num_scrolled), arg);
    func(apr_psprintf(p, "total retrieves since starting: <b>%lu</b> hit, "
                     "<b>%lu</b> miss<br>", header->num_retrieves_hit,
                     header->num_retrieves_miss), arg);
    func(apr_psprintf(p, "total removes since starting: <b>%lu</b> hit, "
                     "<b>%lu</b> miss<br>", header->num_removes_hit,
                     header->num_removes_miss), arg);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, 
                 "leaving shmcb_status");
    return;
}

/*
**
** Memory manipulation and low-level cache operations 
**
*/

static BOOL shmcb_init_memory(
    server_rec *s, void *shm_mem,
    unsigned int shm_mem_size)
{
    SHMCBHeader *header;
    SHMCBQueue queue;
    SHMCBCache cache;
    unsigned int temp, loop, granularity;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, 
                 "entered shmcb_init_memory()");

    /* Calculate some sizes... */
    temp = sizeof(SHMCBHeader);

    /* If the segment is ridiculously too small, bail out */
