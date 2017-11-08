static void memcache_cache_free(void*a)
{
    cache_object_t *obj = (cache_object_t *)a;

    /* Cleanup the cache object. Object should be removed from the cache
     * now. Increment the refcount before setting cleanup to avoid a race 
     * condition. A similar pattern is used in remove_url()
     */
#ifdef USE_ATOMICS
    apr_atomic_inc(&obj->refcount);
#else
    obj->refcount++;
#endif

    obj->cleanup = 1;

#ifdef USE_ATOMICS
    if (!apr_atomic_dec(&obj->refcount)) {
        cleanup_cache_object(obj);
    }
#else
    obj->refcount--;
    if (!obj->refcount) {
        cleanup_cache_object(obj);
    }
#endif
}