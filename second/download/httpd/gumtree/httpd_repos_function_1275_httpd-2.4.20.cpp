static const char *add_cache_enable(cmd_parms *parms, void *dummy,
                                    const char *type,
                                    const char *url)
{
    cache_dir_conf *dconf = (cache_dir_conf *)dummy;
    cache_server_conf *conf;
    struct cache_enable *new;

    const char *err = ap_check_cmd_context(parms,
                                           NOT_IN_DIRECTORY|NOT_IN_LIMIT|NOT_IN_FILES);
    if (err != NULL) {
        return err;
    }

    if (*type == '/') {
        return apr_psprintf(parms->pool,
          "provider (%s) starts with a '/'.  Are url and provider switched?",
          type);
    }

    if (!url) {
        url = parms->path;
    }
    if (!url) {
        return apr_psprintf(parms->pool,
          "CacheEnable provider (%s) is missing an URL.", type);
    }
    if (parms->path && strncmp(parms->path, url, strlen(parms->path))) {
        return "When in a Location, CacheEnable must specify a path or an URL below "
        "that location.";
    }

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);

    if (parms->path) {
        new = apr_array_push(dconf->cacheenable);
        dconf->enable_set = 1;
    }
    else {
        new = apr_array_push(conf->cacheenable);
    }

    new->type = type;
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