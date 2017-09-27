     * non-stale handle.
     */
    h = cache->stale_handle ? cache->stale_handle : cache->handle;
    if (!h) {
       return OK;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                 "cache: Removing url %s from the cache", h->cache_obj->key);

    /* for each specified cache type, delete the URL */
    while(list) {
        list->provider->remove_url(h, p);
        list = list->next;
    }
    return OK;
}


