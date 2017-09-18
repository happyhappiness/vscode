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
