#ifdef POOL_DEBUG
    /* we don't copy keys and values, so it's necessary that
     * overlay->a.pool and base->a.pool have a life span at least
     * as long as p
     */
    if (!apr_pool_is_ancestor(overlay->pool, p)) {
        fprintf(stderr, 
                "apr_hash_overlay: overlay's pool is not an ancestor of p\n");
        abort();
    }
    if (!apr_pool_is_ancestor(base->pool, p)) {
        fprintf(stderr, 
                "apr_hash_overlay: base's pool is not an ancestor of p\n");
        abort();
    }
#endif

    res = apr_palloc(p, sizeof(apr_hash_t));
