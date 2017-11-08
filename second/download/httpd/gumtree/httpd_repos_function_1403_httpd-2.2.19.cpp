apr_status_t ap_http_outerror_filter(ap_filter_t *f,
                                     apr_bucket_brigade *b)
{
    request_rec *r = f->r;
    outerror_filter_ctx_t *ctx = (outerror_filter_ctx_t *)(f->ctx);
    apr_bucket *e;

    /* Create context if none is present */
    if (!ctx) {
        ctx = apr_pcalloc(r->pool, sizeof(outerror_filter_ctx_t));
        f->ctx = ctx;
    }
    for (e = APR_BRIGADE_FIRST(b);
         e != APR_BRIGADE_SENTINEL(b);
         e = APR_BUCKET_NEXT(e))
    {
        if (AP_BUCKET_IS_ERROR(e)) {
            /*
             * Start of error handling state tree. Just one condition
             * right now :)
             */
            if (((ap_bucket_error *)(e->data))->status == HTTP_BAD_GATEWAY) {
                /* stream aborted and we have not ended it yet */
                r->connection->keepalive = AP_CONN_CLOSE;
            }
            continue;
        }
        /* Detect EOC buckets and memorize this in the context. */
        if (AP_BUCKET_IS_EOC(e)) {
            ctx->seen_eoc = 1;
        }
    }
    /*
     * Remove all data buckets that are in a brigade after an EOC bucket
     * was seen, as an EOC bucket tells us that no (further) resource
     * and protocol data should go out to the client. OTOH meta buckets
     * are still welcome as they might trigger needed actions down in
     * the chain (e.g. in network filters like SSL).
     * Remark 1: It is needed to dump ALL data buckets in the brigade
     *           since an filter in between might have inserted data
     *           buckets BEFORE the EOC bucket sent by the original
     *           sender and we do NOT want this data to be sent.
     * Remark 2: Dumping all data buckets here does not necessarily mean
     *           that no further data is send to the client as:
     *           1. Network filters like SSL can still be triggered via
     *              meta buckets to talk with the client e.g. for a
     *              clean shutdown.
     *           2. There could be still data that was buffered before
     *              down in the chain that gets flushed by a FLUSH or an
     *              EOS bucket.
     */
    if (ctx->seen_eoc) {
        for (e = APR_BRIGADE_FIRST(b);
             e != APR_BRIGADE_SENTINEL(b);
             e = APR_BUCKET_NEXT(e))
        {
            if (!APR_BUCKET_IS_METADATA(e)) {
                APR_BUCKET_REMOVE(e);
            }
        }
    }

    return ap_pass_brigade(f->next,  b);
}