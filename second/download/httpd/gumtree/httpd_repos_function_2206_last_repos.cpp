static apr_bucket *bucket_socket_ex_create(socket_ex_data *data,
                                           apr_bucket_alloc_t *list)
{
    apr_bucket *b = apr_bucket_alloc(sizeof(*b), list);

    APR_BUCKET_INIT(b);
    b->free = apr_bucket_free;
    b->list = list;
    return bucket_socket_ex_make(b, data);
}