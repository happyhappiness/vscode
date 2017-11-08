static int remove_url(const char *type, const char *key) 
{
    cache_object_t *obj;

    if (strcasecmp(type, "mem") && strcasecmp(type, "fd")) {
        return DECLINED;
    }
    /* Order of the operations is important to avoid race conditions. 
     * First, remove the object from the cache. Remember, all additions
     * deletions from the cache are protected by sconf->lock.
     * Increment the ref count on the object to indicate our thread
     * is accessing the object. Then set the cleanup flag on the
     * object. Remember, the cleanup flag is NEVER set on an
     * object in the hash table.  If an object has the cleanup
     * flag set, it is guaranteed to NOT be in the hash table.
     */
    if (sconf->lock) {
        apr_thread_mutex_lock(sconf->lock);
    }
  
    obj = cache_find(sconf->cache_cache, key);       
    if (obj) {
        mem_cache_object_t *mobj;
        cache_remove(sconf->cache_cache, obj);
        mobj = (mem_cache_object_t *) obj->vobj;
        sconf->object_cnt--;
        sconf->cache_size -= mobj->m_len;

#ifdef USE_ATOMICS
        /* Refcount increment in this case MUST be made under 
         * protection of the lock 
         */
        apr_atomic_inc(&obj->refcount);
#else
        if (!obj->refcount) {
            cleanup_cache_object(obj);
            obj = NULL;
        }
#endif
        if (obj) {
            obj->cleanup = 1;
        }
    }
    if (sconf->lock) {
        apr_thread_mutex_unlock(sconf->lock);
    }
#ifdef USE_ATOMICS
    if (obj) {
        if (!apr_atomic_dec(&obj->refcount)) {
            cleanup_cache_object(obj);
        }
    }
#endif
    return OK;
}