static void * create_cache_config(apr_pool_t *p, server_rec *s)
{
    const char *tmppath;
    cache_server_conf *ps = apr_pcalloc(p, sizeof(cache_server_conf));

    /* array of URL prefixes for which caching is enabled */
    ps->cacheenable = apr_array_make(p, 10, sizeof(struct cache_enable));
    /* array of URL prefixes for which caching is disabled */
    ps->cachedisable = apr_array_make(p, 10, sizeof(struct cache_disable));
    /* maximum time to cache a document */
    ps->maxex = DEFAULT_CACHE_MAXEXPIRE;
    ps->maxex_set = 0;
    ps->minex = DEFAULT_CACHE_MINEXPIRE;
    ps->minex_set = 0;
    /* default time to cache a document */
    ps->defex = DEFAULT_CACHE_EXPIRE;
    ps->defex_set = 0;
    /* factor used to estimate Expires date from LastModified date */
    ps->factor = DEFAULT_CACHE_LMFACTOR;
    ps->factor_set = 0;
    ps->no_last_mod_ignore_set = 0;
    ps->no_last_mod_ignore = 0;
    ps->ignorecachecontrol = 0;
    ps->ignorecachecontrol_set = 0;
    ps->store_private = 0;
    ps->store_private_set = 0;
    ps->store_nostore = 0;
    ps->store_nostore_set = 0;
    /* array of headers that should not be stored in cache */
    ps->ignore_headers = apr_array_make(p, 10, sizeof(char *));
    ps->ignore_headers_set = CACHE_IGNORE_HEADERS_UNSET;
    /* flag indicating that query-string should be ignored when caching */
    ps->ignorequerystring = 0;
    ps->ignorequerystring_set = 0;
    /* by default, run in the quick handler */
    ps->quick = 1;
    ps->quick_set = 0;
    /* array of identifiers that should not be used for key calculation */
    ps->ignore_session_id = apr_array_make(p, 10, sizeof(char *));
    ps->ignore_session_id_set = CACHE_IGNORE_SESSION_ID_UNSET;
    ps->lock = 0; /* thundering herd lock defaults to off */
    ps->lock_set = 0;
    apr_temp_dir_get(&tmppath, p);
    if (tmppath) {
        ps->lockpath = apr_pstrcat(p, tmppath, DEFAULT_CACHE_LOCKPATH, NULL);
    }
    ps->lockmaxage = apr_time_from_sec(DEFAULT_CACHE_MAXAGE);
    return ps;
}