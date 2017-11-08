static const char *add_cache_disable(cmd_parms *parms, void *dummy,
                                     const char *url)
{
    cache_server_conf *conf;
    struct cache_enable *new;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    new = apr_array_push(conf->cachedisable);
    new->url = url;
    return NULL;
}