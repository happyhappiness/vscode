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
    /* maximum time to cache a document */
    ps->maxex = (overrides->maxex_set == 0) ? base->maxex : overrides->maxex;
    /* default time to cache a document */
    ps->defex = (overrides->defex_set == 0) ? base->defex : overrides->defex;
    /* factor used to estimate Expires date from LastModified date */
    ps->factor =
        (overrides->factor_set == 0) ? base->factor : overrides->factor;

    ps->no_last_mod_ignore =
        (overrides->no_last_mod_ignore_set == 0)
        ? base->no_last_mod_ignore
        : overrides->no_last_mod_ignore;
    ps->ignorecachecontrol  =
        (overrides->ignorecachecontrol_set == 0)
        ? base->ignorecachecontrol
        : overrides->ignorecachecontrol;
    ps->store_private  =
        (overrides->store_private_set == 0)
        ? base->store_private
        : overrides->store_private;
    ps->store_nostore  =
        (overrides->store_nostore_set == 0)
        ? base->store_nostore
        : overrides->store_nostore;
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
    return ps;
}