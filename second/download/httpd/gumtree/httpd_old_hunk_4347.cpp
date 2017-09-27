    apr_bucket *b, *next;

    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        /* even when beam buckets are split, only the one where
         * refcount drops to 0 will call us */
        H2_BPROXY_REMOVE(proxy);
        /* invoked from green thread, the last beam bucket for the red
         * bucket bred is about to be destroyed.
         * remove it from the hold, where it should be now */
        if (proxy->bred) {
            for (b = H2_BLIST_FIRST(&beam->hold); 
                 b != H2_BLIST_SENTINEL(&beam->hold);
                 b = APR_BUCKET_NEXT(b)) {
                 if (b == proxy->bred) {
                    break;
                 }
            }
            if (b != H2_BLIST_SENTINEL(&beam->hold)) {
                /* bucket is in hold as it should be, mark this one
                 * and all before it for purging. We might have placed meta
                 * buckets without a green proxy into the hold before it 
                 * and schedule them for purging now */
                for (b = H2_BLIST_FIRST(&beam->hold); 
                     b != H2_BLIST_SENTINEL(&beam->hold);
                     b = next) {
                    next = APR_BUCKET_NEXT(b);
                    if (b == proxy->bred) {
                        APR_BUCKET_REMOVE(b);
                        H2_BLIST_INSERT_TAIL(&beam->purge, b);
                        break;
                    }
                    else if (APR_BUCKET_IS_METADATA(b)) {
                        APR_BUCKET_REMOVE(b);
                        H2_BLIST_INSERT_TAIL(&beam->purge, b);
                    }
                    else {
                        /* another data bucket before this one in hold. this
                         * is normal since DATA buckets need not be destroyed
                         * in order */
                    }
                }
                
                proxy->bred = NULL;
            }
            else {
                /* it should be there unless we screwed up */
                ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, beam->red_pool, 
                              APLOGNO(03384) "h2_beam(%d-%s): emitted bucket not "
                              "in hold, n=%d", beam->id, beam->tag, 
                              (int)proxy->n);
                AP_DEBUG_ASSERT(!proxy->bred);
            }
        }
        /* notify anyone waiting on space to become available */
        if (!bl.mutex) {
            r_purge_reds(beam);
        }
        else if (beam->m_cond) {
            apr_thread_cond_broadcast(beam->m_cond);
        }
        leave_yellow(beam, &bl);
    }
}

static void report_consumption(h2_bucket_beam *beam, int force)
{
    if (force || beam->received_bytes != beam->reported_consumed_bytes) {
        if (beam->consumed_fn) { 
            beam->consumed_fn(beam->consumed_ctx, beam, beam->received_bytes
                              - beam->reported_consumed_bytes);
        }
        beam->reported_consumed_bytes = beam->received_bytes;
    }
}

static void report_production(h2_bucket_beam *beam, int force)
{
    if (force || beam->sent_bytes != beam->reported_produced_bytes) {
        if (beam->produced_fn) { 
            beam->produced_fn(beam->produced_ctx, beam, beam->sent_bytes
                              - beam->reported_produced_bytes);
        }
        beam->reported_produced_bytes = beam->sent_bytes;
    }
}

static void h2_blist_cleanup(h2_blist *bl)
{
    apr_bucket *e;

    while (!H2_BLIST_EMPTY(bl)) {
        e = H2_BLIST_FIRST(bl);
