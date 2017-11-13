static int remove_entity(cache_handle_t *h) 
{
    cache_object_t *obj = h->cache_obj;

    /* Remove the cache object from the cache under protection */
    if (sconf->lock) {
        apr_thread_mutex_lock(sconf->lock);
    }
    /* If the object is not already marked for cleanup, remove
     * it from the cache and mark it for cleanup. Remember,
     * an object marked for cleanup is by design not in the
     * hash table.
     */
    if (!obj->cleanup) {
        cache_remove(sconf->cache_cache, obj);
        obj->cleanup = 1;
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL, "gcing a cache entry");
    }

    if (sconf->lock) {
        apr_thread_mutex_unlock(sconf->lock);
    }

    return OK;
}