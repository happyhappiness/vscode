static void * merge_cache_config(apr_pool_t *p, void *basev, void *overridesv)
{
    cache_server_conf *ps = apr_pcalloc(p, sizeof(cache_server_conf));
    cache_server_conf *base = (cache_server_conf *) basev;
    cache_server_conf *overrides = (cache_server_conf *) overridesv;

    /* array of URL prefixes for which caching is disabled */
    ps->cachedisable = apr_array_append(p,
                                        base->cachedisable,
                                        overrides->cachedisable);
    /* array of URL prefixes for which caching is enabled */
    ps->cacheenable = apr_array_append(p,
                                       base->cacheenable,
                                       overrides->cacheenable);

    ps->ignorecachecontrol  =
        (overrides->ignorecachecontrol_set == 0)
        ? base->ignorecachecontrol
        : overrides->ignorecachecontrol;
    ps->ignore_headers =
        (overrides->ignore_headers_set == CACHE_IGNORE_HEADERS_UNSET)
        ? base->ignore_headers
        : overrides->ignore_headers;
    ps->ignorequerystring =
        (overrides->ignorequerystring_set == 0)
        ? base->ignorequerystring
        : overrides->ignorequerystring;
    ps->ignore_session_id =
        (overrides->ignore_session_id_set == CACHE_IGNORE_SESSION_ID_UNSET)
        ? base->ignore_session_id
        : overrides->ignore_session_id;
    ps->lock =
        (overrides->lock_set == 0)
        ? base->lock
        : overrides->lock;
    ps->lockpath =
        (overrides->lockpath_set == 0)
        ? base->lockpath
        : overrides->lockpath;
    ps->lockmaxage =
        (overrides->lockmaxage_set == 0)
        ? base->lockmaxage
        : overrides->lockmaxage;
    ps->quick =
        (overrides->quick_set == 0)
        ? base->quick
        : overrides->quick;
    ps->x_cache =
        (overrides->x_cache_set == 0)
        ? base->x_cache
        : overrides->x_cache;
    ps->x_cache_detail =
        (overrides->x_cache_detail_set == 0)
        ? base->x_cache_detail
        : overrides->x_cache_detail;
    ps->base_uri =
        (overrides->base_uri_set == 0)
        ? base->base_uri
        : overrides->base_uri;
    return ps;
}