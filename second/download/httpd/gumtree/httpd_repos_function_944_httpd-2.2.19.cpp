static apr_status_t decrement_refcount(void *arg)
{
    cache_object_t *obj = (cache_object_t *) arg;

    /* If obj->complete is not set, the cache update failed and the
     * object needs to be removed from the cache then cleaned up.
     * The garbage collector may have ejected the object from the
     * cache already, so make sure it is really still in the cache
     * before attempting to remove it.
     */
    if (!obj->complete) {
        cache_object_t *tobj = NULL;
        if (sconf->lock) {
            apr_thread_mutex_lock(sconf->lock);
        }
        tobj = cache_find(sconf->cache_cache, obj->key);
        if (tobj == obj) {
            cache_remove(sconf->cache_cache, obj);
            apr_atomic_dec32(&obj->refcount);
        }
        if (sconf->lock) {
            apr_thread_mutex_unlock(sconf->lock);
        }
    }

    /* If the refcount drops to 0, cleanup the cache object */
    if (!apr_atomic_dec32(&obj->refcount)) {
        cleanup_cache_object(obj);
    }
    return APR_SUCCESS;
}