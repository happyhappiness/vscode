static apr_status_t beam_bucket_read(apr_bucket *b, const char **str, 
                                     apr_size_t *len, apr_read_type_e block)
{
    h2_beam_proxy *d = b->data;
    if (d->bred) {
        const char *data;
        apr_status_t status = apr_bucket_read(d->bred, &data, len, block);
        if (status == APR_SUCCESS) {
            *str = data + b->start;
            *len = b->length;
        }
        return status;
    }
    *str = &Dummy;
    *len = 0;
    return APR_ECONNRESET;
}