    temp -= header->queue_size;
    header->cache_data_offset = (2 * sizeof(unsigned int));
    header->cache_data_size = header->division_size -
                              header->queue_size - header->cache_data_offset;

    /* Output trace info */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "shmcb_init_memory choices follow");
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "division_mask = 0x%02X", header->division_mask);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "division_offset = %u", header->division_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "division_size = %u", header->division_size);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "queue_size = %u", header->queue_size);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "index_num = %u", header->index_num);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "index_offset = %u", header->index_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "index_size = %u", header->index_size);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "cache_data_offset = %u", header->cache_data_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "cache_data_size = %u", header->cache_data_size);

    /* The header is done, make the caches empty */
    for (loop = 0; loop < granularity; loop++) {
        if (!shmcb_get_division(header, &queue, &cache, loop))
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "shmcb_init_memory, " "internal error");
        shmcb_set_safe_uint(cache.first_pos, 0);
        shmcb_set_safe_uint(cache.pos_count, 0);
        shmcb_set_safe_uint(queue.first_pos, 0);
        shmcb_set_safe_uint(queue.pos_count, 0);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving shmcb_init_memory()");
    return TRUE;
}

static BOOL shmcb_store_session(
    server_rec *s, void *shm_segment, UCHAR *id,
    int idlen, SSL_SESSION * pSession,
