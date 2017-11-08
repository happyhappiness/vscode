static void* authn_cache_dircfg_merge(apr_pool_t *pool, void *BASE, void *ADD)
{
    authn_cache_dircfg *base = BASE;
    authn_cache_dircfg *add = ADD;
    authn_cache_dircfg *ret = apr_pmemdup(pool, add, sizeof(authn_cache_dircfg));
    /* preserve context and timeout if not defaults */
    if (add->context == directory) {
        ret->context = base->context;
    }
    if (add->timeout == apr_time_from_sec(300)) {
        ret->timeout = base->timeout;
    }
    if (add->providers == NULL) {
        ret->providers = base->providers;
    }
    return ret;
}