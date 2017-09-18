    /* If the object is not already marked for cleanup, remove
     * it from the cache and mark it for cleanup. Remember,
     * an object marked for cleanup is by design not in the
     * hash table.
     */
    if (!obj->cleanup) {
        mem_cache_object_t *mobj = (mem_cache_object_t *) obj->vobj;
        cache_remove(sconf->cache_cache, obj);
        sconf->object_cnt--;
        sconf->cache_size -= mobj->m_len;
        obj->cleanup = 1;
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL, "gcing a cache entry");
    }

    if (sconf->lock) {
        apr_thread_mutex_unlock(sconf->lock);
