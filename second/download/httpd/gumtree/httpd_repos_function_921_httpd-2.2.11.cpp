static void memcache_cache_free(void*a)
{
    cache_object_t *obj = (cache_object_t *)a;

    /* Decrement the refcount to account for the object being ejected
     * from the cache. If the refcount is 0, free the object.
     */
    if (!apr_atomic_dec32(&obj->refcount)) {
        cleanup_cache_object(obj);
    }
}