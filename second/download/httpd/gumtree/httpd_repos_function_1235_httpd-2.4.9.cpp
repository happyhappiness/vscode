static const char *add_cache_disable(cmd_parms *parms, void *dummy,
                                     const char *url)
{
    cache_dir_conf *dconf = (cache_dir_conf *)dummy;
    cache_server_conf *conf;
    struct cache_disable *new;

    const char *err = ap_check_cmd_context(parms,
                                           NOT_IN_DIRECTORY|NOT_IN_LIMIT|NOT_IN_FILES);
    if (err != NULL) {
        return err;
    }

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);

    if (parms->path) {
        if (!strcasecmp(url, "on")) {
            dconf->disable = 1;
            dconf->disable_set = 1;
            return NULL;
        }
        else {
            return "CacheDisable must be followed by the word 'on' when in a Location.";
        }
    }

    if (!url || (url[0] != '/' && !ap_strchr_c(url, ':'))) {
        return "CacheDisable must specify a path or an URL.";
    }

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