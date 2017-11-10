static const char *add_cache_disable(cmd_parms *parms, void *dummy,
                                     const char *url)
{
    cache_server_conf *conf;
    struct cache_disable *new;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    new = apr_array_push(conf->cachedisable);
    if (apr_uri_parse(parms->pool, url, &(new->url))) {
        return NULL;
    }
    if (new->url.path) {
        new->pathlen = strlen(new->url.path);
    } else {
        new->pathlen = 1;
        new->url.path = "/";
    }
    return NULL;
}