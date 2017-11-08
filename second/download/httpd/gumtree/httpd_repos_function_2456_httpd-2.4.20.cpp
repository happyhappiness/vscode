static int has_param(link_ctx *ctx, const char *param)
{
    const char *p = apr_table_get(ctx->params, param);
    return !!p;
}