apr_bucket *h2_bucket_eos_create(apr_bucket_alloc_t *list,
                                 h2_stream *stream)
{
    apr_bucket *b = apr_bucket_alloc(sizeof(*b), list);

    APR_BUCKET_INIT(b);
    b->free = apr_bucket_free;
    b->list = list;
    b = h2_bucket_eos_make(b, stream);
    if (stream) {
        h2_bucket_eos *h = b->data;
        apr_pool_pre_cleanup_register(stream->pool, &h->stream, bucket_cleanup);
    }
    return b;
}