static BOOL shmcb_insert_encoded_session(
    server_rec *s, SHMCBQueue * queue,
    SHMCBCache * cache,
    unsigned char *encoded,
    unsigned int encoded_len,
    unsigned char *session_id,
    time_t expiry_time)
{
    SHMCBHeader *header;
    SHMCBIndex *idx = NULL;
    unsigned int gap, new_pos, loop, new_offset;
    int need;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "entering shmcb_insert_encoded_session, "
                 "*queue->pos_count = %u",
                 shmcb_get_safe_uint(queue->pos_count));

    /* If there's entries to expire, ditch them first thing. */
    shmcb_expire_division(s, queue, cache);
    header = cache->header;
    gap = header->cache_data_size - shmcb_get_safe_uint(cache->pos_count);
    if (gap < encoded_len) {
        new_pos = shmcb_get_safe_uint(queue->first_pos);
        loop = 0;
        need = (int) encoded_len - (int) gap;
        while ((need > 0) && (loop + 1 < shmcb_get_safe_uint(queue->pos_count))) {
            new_pos = shmcb_cyclic_increment(header->index_num, new_pos, 1);
            loop += 1;
            idx = shmcb_get_index(queue, new_pos);
            need = (int) encoded_len - (int) gap -
                shmcb_cyclic_space(header->cache_data_size,
                                   shmcb_get_safe_uint(cache->first_pos),
                                   shmcb_get_safe_uint(&(idx->offset)));
        }
        if (loop > 0) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "about to scroll %u sessions from %u",
                         loop, shmcb_get_safe_uint(queue->pos_count));
            /* We are removing "loop" items from the cache. */
            shmcb_set_safe_uint(cache->pos_count,
                                shmcb_get_safe_uint(cache->pos_count) -
                                shmcb_cyclic_space(header->cache_data_size,
                                                   shmcb_get_safe_uint(cache->first_pos),
                                                   shmcb_get_safe_uint(&(idx->offset))));
            shmcb_set_safe_uint(cache->first_pos, shmcb_get_safe_uint(&(idx->offset)));
            shmcb_set_safe_uint(queue->pos_count, shmcb_get_safe_uint(queue->pos_count) - loop);
            shmcb_set_safe_uint(queue->first_pos, new_pos);
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "now only have %u sessions",
                         shmcb_get_safe_uint(queue->pos_count));
            /* Update the stats!!! */
            header->num_scrolled += loop;
        }
    }

    /* probably unecessary checks, but I'll leave them until this code
     * is verified. */
    if (shmcb_get_safe_uint(cache->pos_count) + encoded_len >
        header->cache_data_size) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shmcb_insert_encoded_session internal error");
        return FALSE;
    }
    if (shmcb_get_safe_uint(queue->pos_count) == header->index_num) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shmcb_insert_encoded_session internal error");
        return FALSE;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "we have %u bytes and %u indexes free - enough",
                 header->cache_data_size -
                 shmcb_get_safe_uint(cache->pos_count), header->index_num -
                 shmcb_get_safe_uint(queue->pos_count));


    /* HERE WE ASSUME THAT THE NEW SESSION SHOULD GO ON THE END! I'M NOT
     * CHECKING WHETHER IT SHOULD BE GENUINELY "INSERTED" SOMEWHERE.
     *
     * We either fix that, or find out at a "higher" (read "mod_ssl")
     * level whether it is possible to have distinct session caches for
     * any attempted tomfoolery to do with different session timeouts.
     * Knowing in advance that we can have a cache-wide constant timeout
     * would make this stuff *MUCH* more efficient. Mind you, it's very
     * efficient right now because I'm ignoring this problem!!!
     */

    /* Increment to the first unused byte */
    new_offset = shmcb_cyclic_increment(header->cache_data_size,
                                        shmcb_get_safe_uint(cache->first_pos),
                                        shmcb_get_safe_uint(cache->pos_count));
    /* Copy the DER-encoded session into place */
    shmcb_cyclic_ntoc_memcpy(header->cache_data_size, cache->data,
                            new_offset, encoded, encoded_len);
    /* Get the new index that this session is stored in. */
    new_pos = shmcb_cyclic_increment(header->index_num,
                                     shmcb_get_safe_uint(queue->first_pos),
                                     shmcb_get_safe_uint(queue->pos_count));
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "storing in index %u, at offset %u",
                 new_pos, new_offset);
    idx = shmcb_get_index(queue, new_pos);
    if (idx == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shmcb_insert_encoded_session internal error");
        return FALSE;
    }
    shmcb_safe_clear(idx, sizeof(SHMCBIndex));
    shmcb_set_safe_time(&(idx->expires), expiry_time);
    shmcb_set_safe_uint(&(idx->offset), new_offset);

    /* idx->removed = (unsigned char)0; */ /* Not needed given the memset above. */
    idx->s_id2 = session_id[1];
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "session_id[0]=%u, idx->s_id2=%u",
                 session_id[0], session_id[1]);

    /* All that remains is to adjust the cache's and queue's "pos_count"s. */
    shmcb_set_safe_uint(cache->pos_count,
                       shmcb_get_safe_uint(cache->pos_count) + encoded_len);
    shmcb_set_safe_uint(queue->pos_count,
                       shmcb_get_safe_uint(queue->pos_count) + 1);

    /* And just for good debugging measure ... */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving now with %u bytes in the cache and %u indexes",
                 shmcb_get_safe_uint(cache->pos_count),
                 shmcb_get_safe_uint(queue->pos_count));
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving shmcb_insert_encoded_session");
    return TRUE;
}