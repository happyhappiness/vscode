static apr_status_t read_array(request_rec *r, apr_array_header_t *arr,
        unsigned char *buffer, apr_size_t buffer_len, apr_size_t *slider)
{
    apr_size_t val = *slider;

    while (*slider < buffer_len) {
        if (buffer[*slider] == '\r') {
            if (val == *slider) {
                (*slider)++;
                return APR_SUCCESS;
            }
            *((const char **) apr_array_push(arr)) = apr_pstrndup(r->pool,
                    (const char *) buffer + val, *slider - val);
            (*slider)++;
            if (buffer[*slider] == '\n') {
                (*slider)++;
            }
            val = *slider;
        }
        else if (buffer[*slider] == '\0') {
            (*slider)++;
            return APR_SUCCESS;
        }
        else {
            (*slider)++;
        }
    }

    return APR_EOF;
}