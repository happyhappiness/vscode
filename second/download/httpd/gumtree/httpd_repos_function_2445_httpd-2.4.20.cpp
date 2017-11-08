static char *mk_str(link_ctx *ctx, size_t end) 
{
    if (ctx->i < end) {
        return apr_pstrndup(ctx->pool, ctx->s + ctx->i, end - ctx->i);
    }
    return "";
}