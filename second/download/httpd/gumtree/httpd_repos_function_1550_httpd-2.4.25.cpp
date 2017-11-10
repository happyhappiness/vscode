static char *get_cache_value(const char *name, apr_time_t t, char *key,
                             apr_pool_t *p)
{
    cachedmap *map;
    char *val = NULL;

    if (cachep) {
#if APR_HAS_THREADS
        apr_thread_mutex_lock(cachep->lock);
#endif
        map = apr_hash_get(cachep->maps, name, APR_HASH_KEY_STRING);

        if (map) {
            /* if this map is outdated, forget it. */
            if (map->mtime != t) {
                apr_pool_clear(map->pool);
                map->entries = apr_hash_make(map->pool);
                map->mtime = t;
            }
            else {
                val = apr_hash_get(map->entries, key, APR_HASH_KEY_STRING);
                if (val) {
                    /* copy the cached value into the supplied pool,
                     * where it belongs (r->pool usually)
                     */
                    val = apr_pstrdup(p, val);
                }
            }
        }

#if APR_HAS_THREADS
        apr_thread_mutex_unlock(cachep->lock);
#endif
    }

    return val;
}