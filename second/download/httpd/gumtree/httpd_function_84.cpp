static int mem_cache_post_config(apr_pool_t *p, apr_pool_t *plog,
                                 apr_pool_t *ptemp, server_rec *s)
{
    int threaded_mpm;

    /* Sanity check the cache configuration */
    if (sconf->min_cache_object_size >= sconf->max_cache_object_size) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s,
                     "MCacheMaxObjectSize must be greater than MCacheMinObjectSize");
        return DONE;
    }
    if (sconf->max_cache_object_size >= sconf->max_cache_size) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s,
                     "MCacheSize must be greater than MCacheMaxObjectSize");
        return DONE;
    }
    if (sconf->max_streaming_buffer_size > sconf->max_cache_object_size) {
        /* Issue a notice only if something other than the default config 
         * is being used */
        if (sconf->max_streaming_buffer_size != DEFAULT_MAX_STREAMING_BUFFER_SIZE &&
            sconf->max_cache_object_size != DEFAULT_MAX_CACHE_OBJECT_SIZE) {
            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s,
                         "MCacheMaxStreamingBuffer must be less than or equal to MCacheMaxObjectSize. "
                         "Resetting MCacheMaxStreamingBuffer to MCacheMaxObjectSize.");
        }
        sconf->max_streaming_buffer_size = sconf->max_cache_object_size;
    }
    if (sconf->max_streaming_buffer_size < sconf->min_cache_object_size) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "MCacheMaxStreamingBuffer must be greater than or equal to MCacheMinObjectSize. "
                     "Resetting MCacheMaxStreamingBuffer to MCacheMinObjectSize.");
        sconf->max_streaming_buffer_size = sconf->min_cache_object_size;
    }
    ap_mpm_query(AP_MPMQ_IS_THREADED, &threaded_mpm);
    if (threaded_mpm) {
        apr_thread_mutex_create(&sconf->lock, APR_THREAD_MUTEX_DEFAULT, p);
    }

    sconf->cache_cache = cache_init(sconf->max_object_cnt,
                                    sconf->max_cache_size,                                   
                                    memcache_get_priority,
                                    sconf->cache_remove_algorithm,
                                    memcache_get_pos,
                                    memcache_set_pos,
                                    memcache_inc_frequency,
                                    memcache_cache_get_size,
                                    memcache_cache_get_key,
                                    memcache_cache_free);
    apr_pool_cleanup_register(p, sconf, cleanup_cache_mem, apr_pool_cleanup_null);

    if (sconf->cache_cache)
        return OK;

    return -1;

}