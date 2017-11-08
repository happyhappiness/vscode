int cache_create_entity(request_rec *r, apr_off_t size)
{
    cache_provider_list *list;
    cache_handle_t *h = apr_pcalloc(r->pool, sizeof(cache_handle_t));
    char *key;
    apr_status_t rv;
    cache_request_rec *cache = (cache_request_rec *)
                         ap_get_module_config(r->request_config, &cache_module);

    rv = cache_generate_key(r, r->pool, &key);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    list = cache->providers;
    /* for each specified cache type, delete the URL */
    while (list) {
        switch (rv = list->provider->create_entity(h, r, key, size)) {
        case OK: {
            cache->handle = h;
            cache->provider = list->provider;
            cache->provider_name = list->provider_name;
            return OK;
        }
        case DECLINED: {
            list = list->next;
            continue;
        }
        default: {
            return rv;
        }
        }
    }
    return DECLINED;
}