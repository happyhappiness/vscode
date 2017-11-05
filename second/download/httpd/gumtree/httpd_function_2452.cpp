static unsigned int shmcb_expire_division(
    server_rec *s, SHMCBQueue *queue, SHMCBCache *cache)
{
    SHMCBIndex *idx;
    time_t now;
    unsigned int loop, index_num, pos_count, new_pos;
    SHMCBHeader *header;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "entering shmcb_expire_division");

    /* We must calculate num and space ourselves based on expiry times. */
    now = time(NULL);
    loop = 0;
    new_pos = shmcb_get_safe_uint(queue->first_pos);

    /* Cache useful values */
    header = queue->header;
    index_num = header->index_num;
    pos_count = shmcb_get_safe_uint(queue->pos_count);
    while (loop < pos_count) {
        idx = shmcb_get_index(queue, new_pos);
        if (shmcb_get_safe_time(&(idx->expires)) > now)
            /* it hasn't expired yet, we're done iterating */
            break;
        /* This one should be expired too. Shift to the next entry. */
        loop++;
        new_pos = shmcb_cyclic_increment(index_num, new_pos, 1);
    }

    /* Find the new_offset and make the expiries happen. */
    if (loop > 0) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "will be expiring %u sessions", loop);
        /* We calculate the new_offset by "peeking" (or in the
         * case it's the last entry, "sneaking" ;-). */
        if (loop == pos_count) {
            /* We are expiring everything! This is easy to do... */
            shmcb_set_safe_uint(queue->pos_count, 0);
            shmcb_set_safe_uint(cache->pos_count, 0);
        }
        else {
            /* The Queue is easy to adjust */
            shmcb_set_safe_uint(queue->pos_count,
                               shmcb_get_safe_uint(queue->pos_count) - loop);
            shmcb_set_safe_uint(queue->first_pos, new_pos);
            /* peek to the start of the next session */
            idx = shmcb_get_index(queue, new_pos);
            /* We can use shmcb_cyclic_space because we've guaranteed
             * we don't fit the ambiguous full/empty case. */
            shmcb_set_safe_uint(cache->pos_count,
                               shmcb_get_safe_uint(cache->pos_count) -
                               shmcb_cyclic_space(header->cache_data_size,
                                                  shmcb_get_safe_uint(cache->first_pos),
                                                  shmcb_get_safe_uint(&(idx->offset))));
            shmcb_set_safe_uint(cache->first_pos, shmcb_get_safe_uint(&(idx->offset)));
        }
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "we now have %u sessions",
                     shmcb_get_safe_uint(queue->pos_count));
    }
    header->num_expiries += loop;
    return loop;
}