apr_bucket * h2_bucket_observer_create(apr_bucket_alloc_t *list, 
                                       h2_bucket_event_cb *cb, void *ctx)
{
    apr_bucket *b = apr_bucket_alloc(sizeof(*b), list);

    APR_BUCKET_INIT(b);
    b->free = apr_bucket_free;
    b->list = list;
    b = h2_bucket_observer_make(b, cb, ctx);
    return b;
}