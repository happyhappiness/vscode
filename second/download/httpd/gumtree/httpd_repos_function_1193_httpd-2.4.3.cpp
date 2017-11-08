int cache_remove_url(cache_request_rec *cache, request_rec *r)
{
    cache_provider_list *list;
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
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00691)
                 "cache: Removing url %s from the cache", h->cache_obj->key);

    /* for each specified cache type, delete the URL */
    while(list) {
        list->provider->remove_url(h, r);
        list = list->next;
    }
    return OK;
}