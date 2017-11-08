static void preserve(saxctxt *ctx, const size_t len)
{
    char *newbuf;
    if (len <= (ctx->avail - ctx->offset))
        return;
    else while (len > (ctx->avail - ctx->offset))
        ctx->avail += ctx->cfg->bufsz;

    newbuf = realloc(ctx->buf, ctx->avail);
    if (newbuf != ctx->buf) {
        if (ctx->buf)
            apr_pool_cleanup_kill(ctx->f->r->pool, ctx->buf,
                                  (int(*)(void*))free);
        apr_pool_cleanup_register(ctx->f->r->pool, newbuf,
                                  (int(*)(void*))free, apr_pool_cleanup_null);
        ctx->buf = newbuf;
    }
}