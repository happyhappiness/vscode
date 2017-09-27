    header->stat_retrieves_hit = 0;
    header->stat_retrieves_miss = 0;
    header->stat_removes_hit = 0;
    header->stat_removes_miss = 0;
    header->subcache_num = num_subcache;
    /* Convert the subcache size (in bytes) to a value that is suitable for
     * structure alignment on the host platform, by rounding down if necessary. */
    header->subcache_size = (size_t)(shm_segsize / num_subcache);
    if (header->subcache_size != APR_ALIGN_DEFAULT(header->subcache_size)) {
        header->subcache_size = APR_ALIGN_DEFAULT(header->subcache_size) -
                                APR_ALIGN_DEFAULT(1);
    }
    header->subcache_data_offset = ALIGNED_SUBCACHE_SIZE +
                                   num_idx * ALIGNED_INDEX_SIZE;
    header->subcache_data_size = header->subcache_size -
                                 header->subcache_data_offset;
    header->index_num = num_idx;

    /* Output trace info */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00824)
