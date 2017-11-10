static apr_status_t socache_shmcb_init(ap_socache_instance_t *ctx,
                                       const char *namespace,
                                       const struct ap_socache_hints *hints,
                                       server_rec *s, apr_pool_t *p)
{
    void *shm_segment;
    apr_size_t shm_segsize;
    apr_status_t rv;
    SHMCBHeader *header;
    unsigned int num_subcache, num_idx, loop;
    apr_size_t avg_obj_size, avg_id_len;

    /* Create shared memory segment */
    if (ctx->data_file == NULL) {
        const char *path = apr_pstrcat(p, DEFAULT_SHMCB_PREFIX, namespace,
                                       DEFAULT_SHMCB_SUFFIX, NULL);

        ctx->data_file = ap_runtime_dir_relative(p, path);
    }

    /* Use anonymous shm by default, fall back on name-based. */
    rv = apr_shm_create(&ctx->shm, ctx->shm_size, NULL, p);
    if (APR_STATUS_IS_ENOTIMPL(rv)) {
        /* If anon shm isn't supported, fail if no named file was
         * configured successfully; the ap_server_root_relative call
         * above will return NULL for invalid paths. */
        if (ctx->data_file == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00818)
                         "Could not use default path '%s' for shmcb socache",
                         ctx->data_file);
            return APR_EINVAL;
        }

        /* For a name-based segment, remove it first in case of a
         * previous unclean shutdown. */
        apr_shm_remove(ctx->data_file, p);

        rv = apr_shm_create(&ctx->shm, ctx->shm_size, ctx->data_file, p);
    }

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00819)
                     "Could not allocate shared memory segment for shmcb "
                     "socache");
        return rv;
    }

    shm_segment = apr_shm_baseaddr_get(ctx->shm);
    shm_segsize = apr_shm_size_get(ctx->shm);
    if (shm_segsize < (5 * ALIGNED_HEADER_SIZE)) {
        /* the segment is ridiculously small, bail out */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00820)
                     "shared memory segment too small");
        return APR_ENOSPC;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00821)
                 "shmcb_init allocated %" APR_SIZE_T_FMT
                 " bytes of shared memory",
                 shm_segsize);
    /* Discount the header */
    shm_segsize -= ALIGNED_HEADER_SIZE;
    /* Select index size based on average object size hints, if given. */
    avg_obj_size = hints && hints->avg_obj_size ? hints->avg_obj_size : 150;
    avg_id_len = hints && hints->avg_id_len ? hints->avg_id_len : 30;
    num_idx = (shm_segsize) / (avg_obj_size + avg_id_len);
    num_subcache = 256;
    while ((num_idx / num_subcache) < (2 * num_subcache))
        num_subcache /= 2;
    num_idx /= num_subcache;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00822)
                 "for %" APR_SIZE_T_FMT " bytes (%" APR_SIZE_T_FMT
                 " including header), recommending %u subcaches, "
                 "%u indexes each", shm_segsize,
                 shm_segsize + ALIGNED_HEADER_SIZE,
                 num_subcache, num_idx);
    if (num_idx < 5) {
        /* we're still too small, bail out */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00823)
                     "shared memory segment too small");
        return APR_ENOSPC;
    }
    /* OK, we're sorted */
    ctx->header = header = shm_segment;
    header->stat_stores = 0;
    header->stat_replaced = 0;
    header->stat_expiries = 0;
    header->stat_scrolled = 0;
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