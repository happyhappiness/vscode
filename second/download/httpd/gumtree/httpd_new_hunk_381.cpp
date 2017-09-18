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
