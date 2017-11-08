static apr_status_t cleanup_cache_mem(void *sconfv)
{
    cache_object_t *obj;
    mem_cache_conf *co = (mem_cache_conf*) sconfv;

    if (!co) {
        return APR_SUCCESS;
    }
    if (!co->cache_cache) {
        return APR_SUCCESS;
    }

    if (sconf->lock) {
        apr_thread_mutex_lock(sconf->lock);
    }
    obj = cache_pop(co->cache_cache);
    while (obj) {
        /* Iterate over the cache and clean up each unreferenced entry */
        if (!apr_atomic_dec32(&obj->refcount)) {
            cleanup_cache_object(obj);
        }
        obj = cache_pop(co->cache_cache);
    }

    /* Cache is empty, free the cache table */
    cache_free(co->cache_cache);

    if (sconf->lock) {
        apr_thread_mutex_unlock(sconf->lock);
    }
    return APR_SUCCESS;
}