static void *create_cache_config(apr_pool_t *p, server_rec *s)
{
    sconf = apr_pcalloc(p, sizeof(mem_cache_conf));

    sconf->min_cache_object_size = DEFAULT_MIN_CACHE_OBJECT_SIZE;
    sconf->max_cache_object_size = DEFAULT_MAX_CACHE_OBJECT_SIZE;
    /* Number of objects in the cache */
    sconf->max_object_cnt = DEFAULT_MAX_OBJECT_CNT;
    /* Size of the cache in bytes */
    sconf->max_cache_size = DEFAULT_MAX_CACHE_SIZE;
    sconf->cache_cache = NULL;
    sconf->cache_remove_algorithm = memcache_gdsf_algorithm;
    sconf->max_streaming_buffer_size = DEFAULT_MAX_STREAMING_BUFFER_SIZE;

    return sconf;
}