    while (loop < subcache->idx_used) {
        SHMCBIndex *idx = SHMCB_INDEX(subcache, pos);

        /* Only consider 'idx' if the "removed" flag isn't set. */
        if (!idx->removed) {

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00854)
                         "iterating idx=%d, data=%d", pos, idx->data_pos);
            if (idx->expires > now) {
                unsigned char *id = *buf;
                unsigned char *dest;
                unsigned int data_offset, dest_len;
                apr_size_t buf_req;

                /* Find the offset of the data segment, after the id */
                data_offset = SHMCB_CYCLIC_INCREMENT(idx->data_pos,
                                                     idx->id_len,
                                                     header->subcache_data_size);

                dest_len = idx->data_used - idx->id_len;

                buf_req = APR_ALIGN_DEFAULT(idx->id_len + 1)
                        + APR_ALIGN_DEFAULT(dest_len + 1);

                if (buf_req > *buf_len) {
                     /* Grow to ~150% of this buffer requirement on resize
                      * always using APR_ALIGN_DEFAULT sized pages
                      */
