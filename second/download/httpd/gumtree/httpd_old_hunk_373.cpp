    temp -= header->queue_size;
    header->cache_data_offset = (2 * sizeof(unsigned int));
    header->cache_data_size = header->division_size -
                              header->queue_size - header->cache_data_offset;

    /* Output trace info */
    ssl_log(s, SSL_LOG_TRACE, "shmcb_init_memory choices follow");
    ssl_log(s, SSL_LOG_TRACE, "division_mask = 0x%02X", header->division_mask);
    ssl_log(s, SSL_LOG_TRACE, "division_offset = %u", header->division_offset);
    ssl_log(s, SSL_LOG_TRACE, "division_size = %u", header->division_size);
    ssl_log(s, SSL_LOG_TRACE, "queue_size = %u", header->queue_size);
    ssl_log(s, SSL_LOG_TRACE, "index_num = %u", header->index_num);
    ssl_log(s, SSL_LOG_TRACE, "index_offset = %u", header->index_offset);
    ssl_log(s, SSL_LOG_TRACE, "index_size = %u", header->index_size);
    ssl_log(s, SSL_LOG_TRACE, "cache_data_offset = %u", header->cache_data_offset);
    ssl_log(s, SSL_LOG_TRACE, "cache_data_size = %u", header->cache_data_size);

    /* The header is done, make the caches empty */
    for (loop = 0; loop < granularity; loop++) {
        if (!shmcb_get_division(header, &queue, &cache, loop))
            ssl_log(s, SSL_LOG_ERROR, "shmcb_init_memory, " "internal error");
        shmcb_set_safe_uint(cache.first_pos, 0);
        shmcb_set_safe_uint(cache.pos_count, 0);
        shmcb_set_safe_uint(queue.first_pos, 0);
        shmcb_set_safe_uint(queue.pos_count, 0);
    }

    ssl_log(s, SSL_LOG_TRACE, "leaving shmcb_init_memory()");
    return TRUE;
}

static BOOL shmcb_store_session(
    server_rec *s, void *shm_segment, UCHAR *id,
    int idlen, SSL_SESSION * pSession,
