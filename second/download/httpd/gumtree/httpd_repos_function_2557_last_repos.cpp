apr_bucket *h2_bucket_observer_beam(struct h2_bucket_beam *beam,
                                    apr_bucket_brigade *dest,
                                    const apr_bucket *src)
{
    if (H2_BUCKET_IS_OBSERVER(src)) {
        h2_bucket_observer *l = (h2_bucket_observer *)src->data; 
        apr_bucket *b = h2_bucket_observer_create(dest->bucket_alloc, 
                                                  l->cb, l->ctx);
        APR_BRIGADE_INSERT_TAIL(dest, b);
        l->cb = NULL;
        l->ctx = NULL;
        h2_bucket_observer_fire(b, H2_BUCKET_EV_BEFORE_MASTER_SEND);
        return b;
    }
    return NULL;
}