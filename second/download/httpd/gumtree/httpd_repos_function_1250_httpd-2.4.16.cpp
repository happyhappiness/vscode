static void * create_cache_config(apr_pool_t *p, server_rec *s)
{
    const char *tmppath = NULL;
    cache_server_conf *ps = apr_pcalloc(p, sizeof(cache_server_conf));

    /* array of URL prefixes for which caching is enabled */
    ps->cacheenable = apr_array_make(p, 10, sizeof(struct cache_enable));
    /* array of URL prefixes for which caching is disabled */
    ps->cachedisable = apr_array_make(p, 10, sizeof(struct cache_disable));
    ps->ignorecachecontrol = 0;
    ps->ignorecachecontrol_set = 0;
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
    ps->x_cache = DEFAULT_X_CACHE;
    ps->x_cache_detail = DEFAULT_X_CACHE_DETAIL;
    return ps;
}