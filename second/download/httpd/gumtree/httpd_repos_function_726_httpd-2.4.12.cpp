static bio_filter_out_ctx_t *bio_filter_out_ctx_new(ssl_filter_ctx_t *filter_ctx,
                                                    conn_rec *c)
{
    bio_filter_out_ctx_t *outctx = apr_palloc(c->pool, sizeof(*outctx));

    outctx->filter_ctx = filter_ctx;
    outctx->c = c;
    outctx->bb = apr_brigade_create(c->pool, c->bucket_alloc);

    return outctx;
}