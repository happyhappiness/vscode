static apr_bucket *bucket_socket_ex_make(apr_bucket *b, socket_ex_data *data)
{
    b->type        = &bucket_type_socket_ex;
    b->length      = (apr_size_t)(-1);
    b->start       = -1;
    b->data        = data;
    return b;
}