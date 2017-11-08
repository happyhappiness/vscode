static int remove_url(cache_handle_t *h, apr_pool_t *p)
{
    cache_object_t *obj;
    int cleanup = 0;

    if (sconf->lock) {
        apr_thread_mutex_lock(sconf->lock);
    }

    obj = h->cache_obj;
    if (obj && cache_find(sconf->cache_cache, obj->key) == obj) {
        cache_remove(sconf->cache_cache, obj);
        /* For performance, cleanup cache object after releasing the lock */
        cleanup = !apr_atomic_dec32(&obj->refcount);
    }
    if (sconf->lock) {
        apr_thread_mutex_unlock(sconf->lock);
    }

    if (cleanup) {
        cleanup_cache_object(obj);
    }

    return OK;
}