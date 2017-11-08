static int remove_url(const char *key) 
{
    cache_object_t *obj;
    int cleanup = 0;

    if (sconf->lock) {
        apr_thread_mutex_lock(sconf->lock);
    }
  
    obj = cache_find(sconf->cache_cache, key);       
    if (obj) {
        cache_remove(sconf->cache_cache, obj);
        /* For performance, cleanup cache object after releasing the lock */
        cleanup = !apr_atomic_dec(&obj->refcount);
    }
    if (sconf->lock) {
        apr_thread_mutex_unlock(sconf->lock);
    }

    if (cleanup) {
        cleanup_cache_object(obj);
    }

    return OK;
}