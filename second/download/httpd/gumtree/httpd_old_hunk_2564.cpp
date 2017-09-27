     */
    if (header->subcache_data_size - subcache->data_used < total_len
        || subcache->idx_used == header->index_num) {
        unsigned int loop = 0;

        idx = SHMCB_INDEX(subcache, subcache->idx_pos);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "about to force-expire, subcache: idx_used=%d, "
                     "data_used=%d", subcache->idx_used, subcache->data_used);
        do {
            SHMCBIndex *idx2;

            /* Adjust the indexes by one */
