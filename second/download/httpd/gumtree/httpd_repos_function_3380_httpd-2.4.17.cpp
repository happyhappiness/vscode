static void* authn_cache_dircfg_create(apr_pool_t *pool, char *s)
{
    authn_cache_dircfg *ret = apr_palloc(pool, sizeof(authn_cache_dircfg));
    ret->timeout = apr_time_from_sec(300);
    ret->providers = NULL;
    ret->context = directory;
    return ret;
}