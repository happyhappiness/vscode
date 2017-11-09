static void bucket_destroy(void *data)
{
    h2_bucket_observer *h = data;
    if (apr_bucket_shared_destroy(h)) {
        if (h->cb) {
            h->cb(h->ctx, H2_BUCKET_EV_BEFORE_DESTROY, NULL);
        }
        apr_bucket_free(h);
    }
}