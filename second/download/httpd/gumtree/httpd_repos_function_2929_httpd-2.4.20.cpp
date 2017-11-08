static void debug_printf(include_ctx_t *ctx, const char *fmt, ...)
{
    va_list ap;
    char *debug__str;

    va_start(ap, fmt);
    debug__str = apr_pvsprintf(ctx->pool, fmt, ap);
    va_end(ap);

    APR_BRIGADE_INSERT_TAIL(ctx->intern->debug.bb, apr_bucket_pool_create(
                            debug__str, strlen(debug__str), ctx->pool,
                            ctx->intern->debug.f->c->bucket_alloc));
}