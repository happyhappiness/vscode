    apr_hash_t *res;
    apr_hash_entry_t *new_vals = NULL;
    apr_hash_entry_t *iter;
    apr_hash_entry_t *ent;
    unsigned int i,j,k;

#if APR_POOL_DEBUG
    /* we don't copy keys and values, so it's necessary that
     * overlay->a.pool and base->a.pool have a life span at least
     * as long as p
     */
    if (!apr_pool_is_ancestor(overlay->pool, p)) {
        fprintf(stderr,
                "apr_hash_merge: overlay's pool is not an ancestor of p\n");
        abort();
    }
    if (!apr_pool_is_ancestor(base->pool, p)) {
        fprintf(stderr,
                "apr_hash_merge: base's pool is not an ancestor of p\n");
        abort();
    }
#endif

    res = apr_palloc(p, sizeof(apr_hash_t));
    res->pool = p;
    res->free = NULL;
    res->hash_func = base->hash_func;
    res->count = base->count;
    res->max = (overlay->max > base->max) ? overlay->max : base->max;
    if (base->count + overlay->count > res->max) {
        res->max = res->max * 2 + 1;
    }
    res->array = alloc_array(res, res->max);
