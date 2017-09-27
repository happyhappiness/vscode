
    while (loop < subcache->idx_used) {
        SHMCBIndex *idx = SHMCB_INDEX(subcache, pos);

        /* Only consider 'idx' if the id matches, and the "removed"
         * flag isn't set, and the record is not expired.
         * Check the data length too to avoid a buffer overflow 
         * in case of corruption, which should be impossible,
         * but it's cheap to be safe. */
        if (!idx->removed
            && idx->id_len == idlen
            && (idx->data_used - idx->id_len) <= *destlen
            && shmcb_cyclic_memcmp(header->subcache_data_size,
                                   SHMCB_DATA(header, subcache),
                                   idx->data_pos, id, idx->id_len) == 0) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "match at idx=%d, data=%d", pos, idx->data_pos);
            if (idx->expires > now) {
                unsigned int data_offset;

                /* Find the offset of the data segment, after the id */
                data_offset = SHMCB_CYCLIC_INCREMENT(idx->data_pos, 
                                                     idx->id_len,
                                                     header->subcache_data_size);

                *destlen = idx->data_used - idx->id_len;

                /* Copy out the data */
