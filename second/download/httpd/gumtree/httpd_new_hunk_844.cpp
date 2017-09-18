        type_e = CACHE_TYPE_FILE;
    }
    else {
        return DECLINED;
    }

    if (len == -1) {
        /* Caching a streaming response. Assume the response is
         * less than or equal to max_streaming_buffer_size. We will
         * correct all the cache size counters in write_body once
         * we know exactly know how much we are caching.
         */
        len = sconf->max_streaming_buffer_size;
    }

    /* Note: cache_insert() will automatically garbage collect 
     * objects from the cache if the max_cache_size threshold is
     * exceeded. This means mod_mem_cache does not need to implement
     * max_cache_size checks.
     */
    if (len < sconf->min_cache_object_size || 
        len > sconf->max_cache_object_size) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "mem_cache: URL %s failed the size check and will not be cached.",
                     key);
        return DECLINED;
    }

    if (type_e == CACHE_TYPE_FILE) {
        /* CACHE_TYPE_FILE is only valid for local content handled by the 
         * default handler. Need a better way to check if the file is
         * local or not.
         */
        if (!r->filename) {
