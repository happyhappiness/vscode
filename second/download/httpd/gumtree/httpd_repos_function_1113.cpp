static const char *socache_mc_create(ap_socache_instance_t **context, 
                                     const char *arg, 
                                     apr_pool_t *tmp, apr_pool_t *p)
{
    ap_socache_instance_t *ctx;
    
    *context = ctx = apr_palloc(p, sizeof *ctx);

    if (!arg || !*arg) {
        return "List of server names required to create memcache socache.";
    }
    
    ctx->servers = apr_pstrdup(p, arg);

    return NULL;
}