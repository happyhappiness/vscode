static int open_entity(cache_handle_t *h, request_rec *r, const char *type, const char *key) 
{
    cache_object_t *obj;

    /* Look up entity keyed to 'url' */
    if (strcasecmp(type, "mem") && strcasecmp(type, "fd")) {
        return DECLINED;
    }
    if (sconf->lock) {
        apr_thread_mutex_lock(sconf->lock);
    }
    obj = (cache_object_t *) cache_find(sconf->cache_cache, key);
    if (obj) {
        if (obj->complete) {
            request_rec *rmain=r, *rtmp;
#ifdef USE_ATOMICS
            apr_atomic_inc(&obj->refcount);
#else
            obj->refcount++;
#endif
            /* cache is worried about overall counts, not 'open' ones */
            cache_update(sconf->cache_cache, obj);

            /* If this is a subrequest, register the cleanup against
             * the main request. This will prevent the cache object 
             * from being cleaned up from under the request after the
             * subrequest is destroyed.
             */
            rtmp = r;
            while (rtmp) {
                rmain = rtmp;
                rtmp = rmain->main;
            }
            apr_pool_cleanup_register(rmain->pool, obj, decrement_refcount,
                                      apr_pool_cleanup_null);
        }
        else {
            obj = NULL;
        }
    }

    if (sconf->lock) {
        apr_thread_mutex_unlock(sconf->lock);
    }

    if (!obj) {
        return DECLINED;
    }

    /* Initialize the cache_handle */
    h->read_body = &read_body;
    h->read_headers = &read_headers;
    h->write_body = &write_body;
    h->write_headers = &write_headers;
    h->remove_entity = &remove_entity;
    h->cache_obj = obj;
    h->req_hdrs = NULL;  /* Pick these up in read_headers() */
    return OK;
}