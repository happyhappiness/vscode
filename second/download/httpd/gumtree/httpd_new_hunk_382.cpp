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

/* Performs a lookup into a queue/cache pair for a
 * session_id. If found, the session is deserialised
 * and returned, otherwise NULL. */
