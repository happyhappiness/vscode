static int remove_entity(cache_handle_t *h)
{
    cache_object_t *obj = h->cache_obj;
    cache_object_t *tobj = NULL;

    if (sconf->lock) {
        apr_thread_mutex_lock(sconf->lock);
    }

    /* If the entity is still in the cache, remove it and decrement the
     * refcount. If the entity is not in the cache, do nothing. In both cases
     * decrement_refcount called by the last thread referencing the object will
     * trigger the cleanup.
     */
    tobj = cache_find(sconf->cache_cache, obj->key);
    if (tobj == obj) {
        cache_remove(sconf->cache_cache, obj);
        apr_atomic_dec32(&obj->refcount);
    }

    if (sconf->lock) {
        apr_thread_mutex_unlock(sconf->lock);
    }

    return OK;
}