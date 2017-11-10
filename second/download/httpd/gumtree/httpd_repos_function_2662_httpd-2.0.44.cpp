static apr_status_t eos_bucket_read(apr_bucket *b, const char **str, 
                                    apr_size_t *len, apr_read_type_e block)
{
    *str = NULL;
    *len = 0;
    return APR_SUCCESS;
}