                            mc->nSessionCacheDataSize,
                            mc->szSessionCacheDataFile,
                            mc->pPool);
    }

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "could not allocate shared memory for shmcb "
                     "session cache");
        ssl_die();
    }

    shm_segment = apr_shm_baseaddr_get(mc->pSessionCacheDataMM);
    shm_segsize = apr_shm_size_get(mc->pSessionCacheDataMM);
    if (shm_segsize < (5 * sizeof(SHMCBHeader))) {
        /* the segment is ridiculously small, bail out */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shared memory segment too small");
        ssl_die();
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "shmcb_init allocated %" APR_SIZE_T_FMT
                 " bytes of shared memory",
                 shm_segsize);
    /* Discount the header */
    shm_segsize -= sizeof(SHMCBHeader);
    /* Select the number of subcaches to create and how many indexes each
     * should contain based on the size of the memory (the header has already
     * been subtracted). Typical non-client-auth sslv3/tlsv1 sessions are
     * around 150 bytes, so erring to division by 120 helps ensure we would
     * exhaust data storage before index storage (except sslv2, where it's
     * *slightly* the other way). From there, we select the number of subcaches
     * to be a power of two, such that the number of indexes per subcache at
     * least twice the number of subcaches. */
    num_idx = (shm_segsize) / 120;
    num_subcache = 256;
    while ((num_idx / num_subcache) < (2 * num_subcache))
        num_subcache /= 2;
    num_idx /= num_subcache;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "for %" APR_SIZE_T_FMT " bytes (%" APR_SIZE_T_FMT 
                 " including header), recommending %u subcaches, "
                 "%u indexes each", shm_segsize,
                 shm_segsize + sizeof(SHMCBHeader), num_subcache, num_idx);
    if (num_idx < 5) {
        /* we're still too small, bail out */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shared memory segment too small");
        ssl_die();
    }
    /* OK, we're sorted */
    header = shm_segment;
    header->stat_stores = 0;
    header->stat_expiries = 0;
    header->stat_scrolled = 0;
    header->stat_retrieves_hit = 0;
    header->stat_retrieves_miss = 0;
    header->stat_removes_hit = 0;
    header->stat_removes_miss = 0;
    header->subcache_num = num_subcache;
    /* Convert the subcache size (in bytes) to a value that is suitable for
     * structure alignment on the host platform, by rounding down if necessary.
     * This assumes that sizeof(unsigned long) provides an appropriate
     * alignment unit.  */
    header->subcache_size = ((size_t)(shm_segsize / num_subcache) &
                             ~(size_t)(sizeof(unsigned long) - 1));
    header->subcache_data_offset = sizeof(SHMCBSubcache) +
                                   num_idx * sizeof(SHMCBIndex);
    header->subcache_data_size = header->subcache_size -
                                 header->subcache_data_offset;
    header->index_num = num_idx;

    /* Output trace info */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "shmcb_init_memory choices follow");
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "subcache_num = %u", header->subcache_num);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "subcache_size = %u", header->subcache_size);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "subcache_data_offset = %u", header->subcache_data_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "subcache_data_size = %u", header->subcache_data_size);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "index_num = %u", header->index_num);
    /* The header is done, make the caches empty */
    for (loop = 0; loop < header->subcache_num; loop++) {
        SHMCBSubcache *subcache = SHMCB_SUBCACHE(header, loop);
        subcache->idx_pos = subcache->idx_used = 0;
        subcache->data_pos = subcache->data_used = 0;
    }
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "Shared memory session cache initialised");
    /* Success ... */
    mc->tSessionCacheDataTable = shm_segment;
}

void ssl_scache_shmcb_kill(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

