int cache_remove_url(request_rec *r, char *url)
{
    cache_provider_list *list;
    apr_status_t rv;
    char *key;
    cache_request_rec *cache = (cache_request_rec *) 
                         ap_get_module_config(r->request_config, &cache_module);

    rv = cache_generate_key(r,r->pool,&key);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    list = cache->providers;

    /* for each specified cache type, delete the URL */
    while(list) {
        list->provider->remove_url(key);
        list = list->next;
    }
    return OK;
}