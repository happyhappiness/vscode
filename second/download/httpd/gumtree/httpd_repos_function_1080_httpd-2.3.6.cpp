static const char *add_cache_disable(cmd_parms *parms, void *dummy,
                                     const char *url)
{
    cache_server_conf *conf;
    struct cache_disable *new;

    const char *err = ap_check_cmd_context(parms,
                                           NOT_IN_DIRECTORY|NOT_IN_LIMIT|NOT_IN_FILES);
    if (err != NULL) {
        return err;
    }

    if (parms->path && !strcmp(url, "on")) {
        url = parms->path;
    }
    if (url[0] != '/' && !ap_strchr_c(url, ':')) {
        return "CacheDisable must specify a path or an URL, or when in a Location, "
            "the word 'on'.";
    }

    if (parms->path && strncmp(parms->path, url, strlen(parms->path))) {
        return "When in a Location, CacheDisable must specify a path or an URL below "
        "that location.";
    }

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