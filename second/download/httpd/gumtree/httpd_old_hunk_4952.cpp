    cache->out = apr_brigade_create(r->pool, r->connection->bucket_alloc);

    /* save away the possible providers */
    cache->providers = providers;

    /*
     * Try to serve this request from the cache.
     *
     * If no existing cache file (DECLINED)
     *   add cache_save filter
     * If cached file (OK)
     *   clear filter stack
