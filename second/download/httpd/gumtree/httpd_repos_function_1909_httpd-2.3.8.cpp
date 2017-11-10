static void *lb_hb_create_config(apr_pool_t *p, server_rec *s)
{
    lb_hb_ctx_t *ctx = (lb_hb_ctx_t *) apr_palloc(p, sizeof(lb_hb_ctx_t));
    
    ctx->path = ap_server_root_relative(p, "logs/hb.dat");
    
    return ctx;
}