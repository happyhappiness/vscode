static const char *socache_dc_create(ap_socache_instance_t **context,
                                     const char *arg,
                                     apr_pool_t *tmp, apr_pool_t *p)
{
    struct ap_socache_instance_t *ctx;

    ctx = *context = apr_palloc(p, sizeof *ctx);

    ctx->target = apr_pstrdup(p, arg);

    return NULL;
}