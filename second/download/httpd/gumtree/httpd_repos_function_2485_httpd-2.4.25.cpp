apr_bucket * h2_bucket_observer_make(apr_bucket *b, h2_bucket_event_cb *cb,
                                 void *ctx)
{
    h2_bucket_observer *br;

    br = apr_bucket_alloc(sizeof(*br), b->list);
    br->cb = cb;
    br->ctx = ctx;

    b = apr_bucket_shared_make(b, br, 0, 0);
    b->type = &h2_bucket_type_observer;
    return b;
}