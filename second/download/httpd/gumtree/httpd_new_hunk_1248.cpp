    cache_handle_t *h;

    list = cache->providers;

    /* Remove the stale cache entry if present. If not, we're
     * being called from outside of a request; remove the
     * non-stale handle.
     */
    h = cache->stale_handle ? cache->stale_handle : cache->handle;
    if (!h) {
       return OK;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
