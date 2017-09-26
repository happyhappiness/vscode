{
    apr_status_t rv;
    apr_pool_t *pool;
    cache_object_t *obj, *tmp_obj;
    mem_cache_object_t *mobj;

    if (len == -1) {
        /* Caching a streaming response. Assume the response is
         * less than or equal to max_streaming_buffer_size. We will
         * correct all the cache size counters in store_body once
         * we know exactly know how much we are caching.
         */
