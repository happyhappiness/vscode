    }

    /*
     * TODO: Get smarter about managing the cache size. If the cache is 
     * full, we need to garbage collect stale/infrequently referenced
     * objects.
     * we have a self-sizing cache now
    if (sconf->object_cnt >= sconf->max_object_cnt) {
        return DECLINED;
    }
     */
    if (type_e == CACHE_TYPE_HEAP) {
        /* We can safely ignore these measures when caching open fds */
        if (len < sconf->min_cache_object_size || 
            len > sconf->max_cache_object_size) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache_mem: URL %s failed the size check, "
                         "or is incomplete", 
                         key);
            return DECLINED;
        }
        /*
         * not needed now we have a self-sizing cache.
        if ((sconf->cache_size + len) > sconf->max_cache_size) {
            return DECLINED;
        }
        */
    } else {
        /* CACHE_TYPE_FILE is only valid for local content 
         * handled by the default handler? 
         * This is not the right check...
         */
        if (!r->filename) {
