static void alloc_outbuf(sed_filter_ctxt* ctx)
{
    ctx->outbuf = apr_palloc(ctx->tpool, ctx->bufsize + 1);
    ctx->curoutbuf = ctx->outbuf;
}