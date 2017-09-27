 * other entities already exist for the same URL.
 *
 * The size of the entity is provided so that a cache module can
 * decide whether or not it wants to cache this particular entity.
 * If the size is unknown, a size of -1 should be set.
 */
int cache_create_entity(cache_request_rec *cache, request_rec *r,
                        apr_off_t size, apr_bucket_brigade *in)
{
    cache_provider_list *list;
    cache_handle_t *h = apr_pcalloc(r->pool, sizeof(cache_handle_t));
    apr_status_t rv;

    if (!cache) {
        /* This should never happen */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, r, APLOGNO(00692)
                "cache: No cache request information available for key"
                " generation");
        return APR_EGENERAL;
    }

    if (!cache->key) {
        rv = cache_generate_key(r, r->pool, &cache->key);
        if (rv != APR_SUCCESS) {
            return rv;
        }
    }

    list = cache->providers;
    /* for each specified cache type, delete the URL */
    while (list) {
        switch (rv = list->provider->create_entity(h, r, cache->key, size, in)) {
        case OK: {
            cache->handle = h;
            cache->provider = list->provider;
            cache->provider_name = list->provider_name;
            return OK;
        }
