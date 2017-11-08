static const char *add_cache_enable(cmd_parms *parms, void *dummy, 
                                    const char *type, 
                                    const char *url)
{
    cache_server_conf *conf;
    struct cache_enable *new;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    new = apr_array_push(conf->cacheenable);
    new->type = type;
    new->url = url;
    new->urllen = strlen(url);
    return NULL;
}