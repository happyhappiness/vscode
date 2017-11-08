static const char *lookup_header(const char *name, rewrite_ctx *ctx)
{
    const char *val = apr_table_get(ctx->r->headers_in, name);

    if (val) {
        ctx->vary_this = ctx->vary_this
                         ? apr_pstrcat(ctx->r->pool, ctx->vary_this, ", ",
                                       name, NULL)
                         : apr_pstrdup(ctx->r->pool, name);
    }

    return val;
}