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
