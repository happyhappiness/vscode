 * selected, details of it are stored in the per request
 * config to save time when serving the request later.
 *
 * This function returns OK if successful, DECLINED if no
 * cached entity fits the bill.
 */
int cache_select(request_rec *r)
{
    cache_provider_list *list;
    apr_status_t rv;
    cache_handle_t *h;
    char *key;
    cache_request_rec *cache = (cache_request_rec *)
                         ap_get_module_config(r->request_config, &cache_module);

    rv = cache_generate_key(r, r->pool, &key);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    /* go through the cache types till we get a match */
    h = apr_palloc(r->pool, sizeof(cache_handle_t));

    list = cache->providers;

    while (list) {
