static void set_cache_value(const char *name, apr_time_t t, char *key,
                            char *val)
{
    cachedmap *map;

    if (cachep) {
#if APR_HAS_THREADS
        apr_thread_mutex_lock(cachep->lock);
#endif
        map = apr_hash_get(cachep->maps, name, APR_HASH_KEY_STRING);

        if (!map) {
            apr_pool_t *p;

            if (apr_pool_create(&p, cachep->pool) != APR_SUCCESS) {
#if APR_HAS_THREADS
                apr_thread_mutex_unlock(cachep->lock);
#endif
                return;
            }

            map = apr_palloc(cachep->pool, sizeof(cachedmap));
            map->pool = p;
            map->entries = apr_hash_make(map->pool);
            map->mtime = t;

            apr_hash_set(cachep->maps, name, APR_HASH_KEY_STRING, map);
        }
        else if (map->mtime != t) {
            apr_pool_clear(map->pool);
            map->entries = apr_hash_make(map->pool);
            map->mtime = t;
        }

        /* Now we should have a valid map->entries hash, where we
         * can store our value.
         *
         * We need to copy the key and the value into OUR pool,
         * so that we don't leave it during the r->pool cleanup.
         */
        apr_hash_set(map->entries,
                     apr_pstrdup(map->pool, key), APR_HASH_KEY_STRING,
                     apr_pstrdup(map->pool, val));

#if APR_HAS_THREADS
        apr_thread_mutex_unlock(cachep->lock);
#endif
    }

    return;
}