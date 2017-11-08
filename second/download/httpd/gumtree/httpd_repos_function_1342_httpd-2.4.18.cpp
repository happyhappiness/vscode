static void *merge_config(apr_pool_t *p, void *basev, void *overridesv)
{
    cache_socache_conf *ps;
    cache_socache_conf *base = (cache_socache_conf *) basev;
    cache_socache_conf *overrides = (cache_socache_conf *) overridesv;

    /* socache server config only has one field */
    ps = overrides ? overrides : base;

    return ps;
}