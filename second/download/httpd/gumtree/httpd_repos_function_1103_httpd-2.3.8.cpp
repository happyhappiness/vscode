static const char *socache_dbm_create(ap_socache_instance_t **context, 
                                      const char *arg, 
                                      apr_pool_t *tmp, apr_pool_t *p)
{
    ap_socache_instance_t *ctx;

    *context = ctx = apr_pcalloc(p, sizeof *ctx);

    if (arg && *arg) {
        ctx->data_file = ap_server_root_relative(p, arg);
        if (!ctx->data_file) {
            return apr_psprintf(tmp, "Invalid cache file path %s", arg);
        }
    }

    apr_pool_create(&ctx->pool, p);

    return NULL;
}