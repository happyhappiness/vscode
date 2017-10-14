ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving now with %u bytes in the cache and %u indexes",
                 shmcb_get_safe_uint(cache->pos_count),
                 shmcb_get_safe_uint(queue->pos_count));