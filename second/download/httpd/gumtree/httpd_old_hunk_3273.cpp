AP_DECLARE(int) ap_sys_privileges_handlers(int inc)
{
    sys_privileges += inc;
    return sys_privileges;
}

static int core_pre_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp)
{
    ap_mutex_init(pconf);
    return APR_SUCCESS;
}

static int core_post_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    ap__logio_add_bytes_out = APR_RETRIEVE_OPTIONAL_FN(ap_logio_add_bytes_out);
    ident_lookup = APR_RETRIEVE_OPTIONAL_FN(ap_ident_lookup);
