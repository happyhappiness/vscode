
    apr_pool_create(&ctx->pool, p);

    return NULL;
}

static apr_status_t socache_dbm_init(ap_socache_instance_t *ctx, 
                                     const char *namespace, 
                                     const struct ap_socache_hints *hints,
                                     server_rec *s, apr_pool_t *p)
{
    apr_dbm_t *dbm;
    apr_status_t rv;

