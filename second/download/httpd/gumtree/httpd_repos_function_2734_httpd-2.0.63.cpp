static apr_status_t heap_bucket_read(apr_bucket *b, const char **str, 
                                     apr_size_t *len, apr_read_type_e block)
{
    apr_bucket_heap *h = b->data;

    *str = h->base + b->start;
    *len = b->length;
    return APR_SUCCESS;
}