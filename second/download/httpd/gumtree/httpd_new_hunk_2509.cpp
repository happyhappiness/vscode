 * selected, details of it are stored in the per request
 * config to save time when serving the request later.
 *
 * This function returns OK if successful, DECLINED if no
 * cached entity fits the bill.
 */
int cache_select(cache_request_rec *cache, request_rec *r)
{
    cache_provider_list *list;
    apr_status_t rv;
    cache_handle_t *h;

    if (!cache) {
        /* This should never happen */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, r, APLOGNO(00693)
                "cache: No cache request information available for key"
                " generation");
        return DECLINED;
    }

    if (!cache->key) {
        rv = cache_generate_key(r, r->pool, &cache->key);
        if (rv != APR_SUCCESS) {
            return DECLINED;
        }
    }

    if (!ap_cache_check_allowed(cache, r)) {
        return DECLINED;
    }

    /* go through the cache types till we get a match */
    h = apr_palloc(r->pool, sizeof(cache_handle_t));

    list = cache->providers;

    while (list) {
