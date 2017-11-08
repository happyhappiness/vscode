static apr_status_t store_array(apr_array_header_t *arr, unsigned char *buffer,
        apr_size_t buffer_len, apr_size_t *slider)
{
    int i, len;
    const char **elts;

    elts = (const char **) arr->elts;

    for (i = 0; i < arr->nelts; i++) {
        len = strlen(elts[i]);
        if (len + 3 >= buffer_len - *slider) {
            return APR_EOF;
        }
        len = apr_snprintf(buffer ? (char *) buffer + *slider : NULL,
                buffer ? buffer_len - *slider : 0, "%s" CRLF, elts[i]);
        *slider += len;
    }
    if (buffer) {
        memcpy(buffer + *slider, CRLF, sizeof(CRLF) - 1);
    }
    *slider += sizeof(CRLF) - 1;

    return APR_SUCCESS;
}