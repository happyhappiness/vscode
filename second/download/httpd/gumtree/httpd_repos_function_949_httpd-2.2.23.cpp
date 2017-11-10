static int create_entity(cache_handle_t *h, cache_type_e type_e,
                         request_rec *r, const char *key, apr_off_t len)
{
    apr_status_t rv;
    apr_pool_t *pool;
    cache_object_t *obj, *tmp_obj;
    mem_cache_object_t *mobj;

    /* we don't support caching of range requests (yet) */
    if (r->status == HTTP_PARTIAL_CONTENT) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "disk_cache: URL %s partial content response not cached",
                     key);
        return DECLINED;
    }

    if (len == -1) {
        /* Caching a streaming response. Assume the response is
         * less than or equal to max_streaming_buffer_size. We will
         * correct all the cache size counters in store_body once
         * we know exactly know how much we are caching.
         */
        len = sconf->max_streaming_buffer_size;
    }

    /* Note: cache_insert() will automatically garbage collect
     * objects from the cache if the max_cache_size threshold is
     * exceeded. This means mod_mem_cache does not need to implement
     * max_cache_size checks.
     */
    if (len < sconf->min_cache_object_size ||
        len > sconf->max_cache_object_size) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "mem_cache: URL %s failed the size check and will not be cached.",
                     key);
        return DECLINED;
    }

    if (type_e == CACHE_TYPE_FILE) {
        /* CACHE_TYPE_FILE is only valid for local content handled by the
         * default handler. Need a better way to check if the file is
         * local or not.
         */
        if (!r->filename) {
            return DECLINED;
        }
    }

    rv = apr_pool_create(&pool, NULL);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
                     "mem_cache: Failed to create memory pool.");
        return DECLINED;
    }

    /* Allocate and initialize cache_object_t */
    obj = apr_pcalloc(pool, sizeof(*obj));
    obj->key = apr_pstrdup(pool, key);

    /* Allocate and init mem_cache_object_t */
    mobj = apr_pcalloc(pool, sizeof(*mobj));
    mobj->pool = pool;

    if (threaded_mpm) {
        apr_thread_mutex_create(&mobj->lock, APR_THREAD_MUTEX_DEFAULT, pool);
    }

    /* Finish initing the cache object */
    apr_atomic_set32(&obj->refcount, 1);
    mobj->total_refs = 1;
    obj->complete = 0;
    obj->vobj = mobj;
    /* Safe cast: We tested < sconf->max_cache_object_size above */
    mobj->m_len = (apr_size_t)len;
    mobj->type = type_e;

    /* Place the cache_object_t into the hash table.
     * Note: Perhaps we should wait to put the object in the
     * hash table when the object is complete?  I add the object here to
     * avoid multiple threads attempting to cache the same content only
     * to discover at the very end that only one of them will succeed.
     * Furthermore, adding the cache object to the table at the end could
     * open up a subtle but easy to exploit DoS hole: someone could request
     * a very large file with multiple requests. Better to detect this here
     * rather than after the cache object has been completely built and
     * initialized...
     * XXX Need a way to insert into the cache w/o such coarse grained locking
     */
    if (sconf->lock) {
        apr_thread_mutex_lock(sconf->lock);
    }
    tmp_obj = (cache_object_t *) cache_find(sconf->cache_cache, key);

    if (!tmp_obj) {
        cache_insert(sconf->cache_cache, obj);
        /* Add a refcount to account for the reference by the
         * hashtable in the cache. Refcount should be 2 now, one
         * for this thread, and one for the cache.
         */
        apr_atomic_inc32(&obj->refcount);
    }
    if (sconf->lock) {
        apr_thread_mutex_unlock(sconf->lock);
    }

    if (tmp_obj) {
        /* This thread collided with another thread loading the same object
         * into the cache at the same time. Defer to the other thread which
         * is further along.
         */
        cleanup_cache_object(obj);
        return DECLINED;
    }

    apr_pool_cleanup_register(r->pool, obj, decrement_refcount,
                              apr_pool_cleanup_null);

    /* Populate the cache handle */
    h->cache_obj = obj;

    return OK;
}