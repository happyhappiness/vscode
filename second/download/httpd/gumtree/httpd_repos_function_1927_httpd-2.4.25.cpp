static void *hb_create_config(apr_pool_t *p, server_rec *s)
{
    hb_ctx_t *cfg = (hb_ctx_t *) apr_pcalloc(p, sizeof(hb_ctx_t));

    return cfg;
}