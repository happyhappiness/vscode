                                   num_idx * sizeof(SHMCBIndex);
    header->subcache_data_size = header->subcache_size -
                                 header->subcache_data_offset;
    header->index_num = num_idx;

    /* Output trace info */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00824)
                 "shmcb_init_memory choices follow");
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00825)
                 "subcache_num = %u", header->subcache_num);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00826)
                 "subcache_size = %u", header->subcache_size);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00827)
                 "subcache_data_offset = %u", header->subcache_data_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00828)
                 "subcache_data_size = %u", header->subcache_data_size);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00829)
                 "index_num = %u", header->index_num);
    /* The header is done, make the caches empty */
    for (loop = 0; loop < header->subcache_num; loop++) {
        SHMCBSubcache *subcache = SHMCB_SUBCACHE(header, loop);
        subcache->idx_pos = subcache->idx_used = 0;
        subcache->data_pos = subcache->data_used = 0;
    }
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(00830)
                 "Shared memory socache initialised");
    /* Success ... */

    return APR_SUCCESS;
}

