        /* Only consider 'idx' if the id matches, and the "removed"
         * flag isn't set. */
        if (!idx->removed && idx->id_len == idlen
            && shmcb_cyclic_memcmp(header->subcache_data_size,
                                   SHMCB_DATA(header, subcache),
                                   idx->data_pos, id, idx->id_len) == 0) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00852)
                         "possible match at idx=%d, data=%d", pos, idx->data_pos);

            /* Found the matching entry, remove it quietly. */
            idx->removed = 1;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00853)
                         "shmcb_subcache_remove removing matching entry");
            return 0;
        }
        /* Increment */
        loop++;
        pos = SHMCB_CYCLIC_INCREMENT(pos, 1, header->index_num);
