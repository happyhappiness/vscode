static apr_status_t decrement_refcount(void *arg) 
{
    cache_object_t *obj = (cache_object_t *) arg;

    /* If obj->complete is not set, the cache update failed and the
     * object needs to be removed from the cache then cleaned up.
     */
    if (!obj->complete) {
        mem_cache_object_t *mobj = (mem_cache_object_t *) obj->vobj;
        if (sconf->lock) {
            apr_thread_mutex_lock(sconf->lock);
        }
        /* Remember, objects marked for cleanup are, by design, already
         * removed from the cache. remove_url() could have already
         * removed the object from the cache (and set obj->cleanup)
         */
        if (!obj->cleanup) {
            cache_remove(sconf->cache_cache, obj);
            sconf->object_cnt--;
            sconf->cache_size -= mobj->m_len;
            obj->cleanup = 1;
        }
        if (sconf->lock) {
            apr_thread_mutex_unlock(sconf->lock);
        }
    }

    /* Cleanup the cache object */
#ifdef USE_ATOMICS
    if (!apr_atomic_dec(&obj->refcount)) {
        if (obj->cleanup) {
            cleanup_cache_object(obj);
        }
    }
#else
    if (sconf->lock) {
        apr_thread_mutex_lock(sconf->lock);
    }
    obj->refcount--;
    /* If the object is marked for cleanup and the refcount
     * has dropped to zero, cleanup the object
     */
    if ((obj->cleanup) && (!obj->refcount)) {
        cleanup_cache_object(obj);
    }
    if (sconf->lock) {
        apr_thread_mutex_unlock(sconf->lock);
    }
#endif
    return APR_SUCCESS;
}