ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "we have %u bytes and %u indexes free - enough",
                 header->cache_data_size -
                 shmcb_get_safe_uint(cache->pos_count), header->index_num -
                 shmcb_get_safe_uint(queue->pos_count));