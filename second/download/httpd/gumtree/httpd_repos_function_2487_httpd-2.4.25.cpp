apr_status_t h2_bucket_observer_fire(apr_bucket *b, h2_bucket_event event)
{
    if (H2_BUCKET_IS_OBSERVER(b)) {
        h2_bucket_observer *l = (h2_bucket_observer *)b->data; 
        return l->cb(l->ctx, event, b);
    }
    return APR_EINVAL;
}