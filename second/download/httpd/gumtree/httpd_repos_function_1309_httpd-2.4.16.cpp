static apr_status_t read_table(cache_handle_t *handle, request_rec *r,
        apr_table_t *table, unsigned char *buffer, apr_size_t buffer_len,
        apr_size_t *slider)
{
    apr_size_t key = *slider, colon = 0, len = 0;
    ;

    while (*slider < buffer_len) {
        if (buffer[*slider] == ':') {
            if (!colon) {
                colon = *slider;
            }
            (*slider)++;
        }
        else if (buffer[*slider] == '\r') {
            len = colon;
            if (key == *slider) {
                (*slider)++;
                if (buffer[*slider] == '\n') {
                    (*slider)++;
                }
                return APR_SUCCESS;
            }
            if (!colon || buffer[colon++] != ':') {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02344)
                        "Premature end of cache headers.");
                return APR_EGENERAL;
            }
            while (apr_isspace(buffer[colon])) {
                colon++;
            }
            apr_table_addn(table, apr_pstrndup(r->pool, (const char *) buffer
                    + key, len - key), apr_pstrndup(r->pool,
                    (const char *) buffer + colon, *slider - colon));
            (*slider)++;
            if (buffer[*slider] == '\n') {
                (*slider)++;
            }
            key = *slider;
            colon = 0;
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