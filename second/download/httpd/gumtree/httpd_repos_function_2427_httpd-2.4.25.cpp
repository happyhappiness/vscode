apr_bucket * h2_bucket_eoc_make(apr_bucket *b, h2_session *session)
{
    h2_bucket_eoc *h;

    h = apr_bucket_alloc(sizeof(*h), b->list);
    h->session = session;

    b = apr_bucket_shared_make(b, h, 0, 0);
    b->type = &h2_bucket_type_eoc;
    
    return b;
}