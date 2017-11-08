static apr_status_t simple_bucket_read(apr_bucket *b, const char **str, 
                                       apr_size_t *len, apr_read_type_e block)
{
    *str = (char *)b->data + b->start;
    *len = b->length;
    return APR_SUCCESS;
}