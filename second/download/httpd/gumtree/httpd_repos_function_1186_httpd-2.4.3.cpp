cache_provider_list *cache_get_providers(request_rec *r,
        cache_server_conf *conf,
        apr_uri_t uri)
{
    cache_dir_conf *dconf = ap_get_module_config(r->per_dir_config, &cache_module);
    cache_provider_list *providers = NULL;
    int i;

    /* per directory cache disable */
    if (dconf->disable) {
        return NULL;
    }

    /* global cache disable */
    for (i = 0; i < conf->cachedisable->nelts; i++) {
        struct cache_disable *ent =
                               (struct cache_disable *)conf->cachedisable->elts;
        if (uri_meets_conditions(&ent[i].url, ent[i].pathlen, &uri)) {
            /* Stop searching now. */
            return NULL;
        }
    }

    /* loop through all the per directory cacheenable entries */
    for (i = 0; i < dconf->cacheenable->nelts; i++) {
        struct cache_enable *ent =
                                (struct cache_enable *)dconf->cacheenable->elts;
        providers = get_provider(r, &ent[i], providers);
    }

    /* loop through all the global cacheenable entries */
    for (i = 0; i < conf->cacheenable->nelts; i++) {
        struct cache_enable *ent =
                                (struct cache_enable *)conf->cacheenable->elts;
        if (uri_meets_conditions(&ent[i].url, ent[i].pathlen, &uri)) {
            providers = get_provider(r, &ent[i], providers);
        }
    }

    return providers;
}