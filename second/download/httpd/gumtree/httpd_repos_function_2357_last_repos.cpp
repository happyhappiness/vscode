apr_bucket *h2_bucket_eos_make(apr_bucket *b, h2_stream *stream)
{
    h2_bucket_eos *h;

    h = apr_bucket_alloc(sizeof(*h), b->list);
    h->stream = stream;

    b = apr_bucket_shared_make(b, h, 0, 0);
    b->type = &h2_bucket_type_eos;
    
    return b;
}