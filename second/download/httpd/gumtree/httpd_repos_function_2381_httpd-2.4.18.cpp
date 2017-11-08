apr_bucket * h2_bucket_eoc_create(apr_bucket_alloc_t *list, h2_session *session)
{
    apr_bucket *b = apr_bucket_alloc(sizeof(*b), list);

    APR_BUCKET_INIT(b);
    b->free = apr_bucket_free;
    b->list = list;
    b = h2_bucket_eoc_make(b, session);
    if (session) {
        h2_bucket_eoc *h = b->data;
        apr_pool_pre_cleanup_register(session->pool, &h->session, bucket_cleanup);
    }
    return b;
}