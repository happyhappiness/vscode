static apr_bucket *cgi_bucket_dup(struct cgi_bucket_data *data,
                                  apr_bucket_alloc_t *list)
{
    apr_bucket *b = apr_bucket_alloc(sizeof(*b), list);
    APR_BUCKET_INIT(b);
    b->free = apr_bucket_free;
    b->list = list;
    b->type = &bucket_type_cgi;
    b->length = (apr_size_t)(-1);
    b->start = -1;
    b->data = data;
    return b;
}