static void init_params(link_ctx *ctx) 
{
    if (!ctx->params) {
        ctx->params = apr_table_make(ctx->pool, 5);
    }
    else {
        apr_table_clear(ctx->params);
    }
}