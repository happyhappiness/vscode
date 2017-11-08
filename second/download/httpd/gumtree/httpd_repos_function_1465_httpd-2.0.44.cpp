static int create_entity(cache_handle_t *h, request_rec *r,
                         const char *type, 
                         const char *key, 
                         apr_off_t len) 
{
    cache_object_t *obj, *tmp_obj;
    mem_cache_object_t *mobj;
    cache_type_e type_e;
    apr_size_t key_len;

    if (!strcasecmp(type, "mem")) {
        type_e = CACHE_TYPE_HEAP;
    } 
    else if (!strcasecmp(type, "fd")) {
        type_e = CACHE_TYPE_FILE;
    }
    else {
        return DECLINED;
    }

    if (len == -1) {
        /* Caching a streaming response. Assume the response is
         * less than or equal to max_streaming_buffer_size. We will
         * correct all the cache size counters in write_body once
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

    /* Allocate and initialize cache_object_t */
    obj = calloc(1, sizeof(*obj));
    if (!obj) {
        return DECLINED;
    }
    key_len = strlen(key) + 1;
    obj->key = malloc(key_len);
    if (!obj->key) {
        cleanup_cache_object(obj);
        return DECLINED;
    }
    memcpy(obj->key, key, key_len);
    /* Safe cast: We tested < sconf->max_cache_object_size above */
    obj->info.len = (apr_size_t)len;

    /* Allocate and init mem_cache_object_t */
    mobj = calloc(1, sizeof(*mobj));
    if (!mobj) {
        cleanup_cache_object(obj);
        return DECLINED;
    }

    /* Finish initing the cache object */
#ifdef USE_ATOMICS
    apr_atomic_set(&obj->refcount, 1);
#else 
    obj->refcount = 1;
#endif
    mobj->total_refs = 1;
    obj->complete = 0;
    obj->cleanup = 0;
    obj->vobj = mobj;
    /* Safe cast: We tested < sconf->max_cache_object_size above */
    mobj->m_len = (apr_size_t)len;
    mobj->type = type_e;

    /* Place the cache_object_t into the hash table.
     * Note: Perhaps we should wait to put the object in the
     * hash table when the object is complete?  I add the object here to
     * avoid multiple threads attempting to cache the same content only
     * to discover at the very end that only one of them will suceed.
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
        sconf->object_cnt++;
        /* Safe cast: Must fit in cache_size or alloc would have failed */
        sconf->cache_size += (apr_size_t)len;
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
    h->read_body = &read_body;
    h->read_headers = &read_headers;
    h->write_body = &write_body;
    h->write_headers = &write_headers;
    h->remove_entity = &remove_entity;

    return OK;
}