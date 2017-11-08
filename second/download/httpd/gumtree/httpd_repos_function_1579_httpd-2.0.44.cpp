int cache_create_entity(request_rec *r, const char *types, char *url, apr_off_t size)
{
    cache_handle_t *h = apr_pcalloc(r->pool, sizeof(cache_handle_t));
    const char *next = types;
    const char *type;
    char *key;
    apr_status_t rv;
    cache_request_rec *cache = (cache_request_rec *) 
                         ap_get_module_config(r->request_config, &cache_module);

    rv =  cache_generate_key(r,r->pool,&key);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    /* for each specified cache type, delete the URL */
    while (next) {
        type = ap_cache_tokstr(r->pool, next, &next);
        switch (rv = cache_run_create_entity(h, r, type, key, size)) {
        case OK: {
            cache->handle = h;
            return OK;
        }
        case DECLINED: {
            continue;
        }
        default: {
            return rv;
        }
        }
    }
    return DECLINED;
}