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
