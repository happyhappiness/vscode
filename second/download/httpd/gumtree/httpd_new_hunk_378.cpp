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
