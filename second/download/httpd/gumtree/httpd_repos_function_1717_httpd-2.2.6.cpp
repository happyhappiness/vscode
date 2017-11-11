int APR_THREAD_FUNC GetServerVariable (isapi_cid    *cid,
                                       char         *variable_name,
                                       void         *buf_ptr,
                                       apr_uint32_t *buf_size)
{
    request_rec *r = cid->r;
    const char *result;
    char *buf_data = (char*)buf_ptr;
    apr_uint32_t len;

    if (!strcmp(variable_name, "ALL_HTTP"))
    {
        /* crlf delimited, colon split, comma separated and
         * null terminated list of HTTP_ vars
         */
        const apr_array_header_t *arr = apr_table_elts(r->subprocess_env);
        const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;
        int i;

        for (len = 0, i = 0; i < arr->nelts; i++) {
            if (!strncmp(elts[i].key, "HTTP_", 5)) {
                len += strlen(elts[i].key) + strlen(elts[i].val) + 3;
            }
        }

        if (*buf_size < len + 1) {
            *buf_size = len + 1;
            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INSUFFICIENT_BUFFER));
            return 0;
        }

        for (i = 0; i < arr->nelts; i++) {
            if (!strncmp(elts[i].key, "HTTP_", 5)) {
                strcpy(buf_data, elts[i].key);
                buf_data += strlen(elts[i].key);
                *(buf_data++) = ':';
                strcpy(buf_data, elts[i].val);
                buf_data += strlen(elts[i].val);
                *(buf_data++) = '\r';
                *(buf_data++) = '\n';
            }
        }

        *(buf_data++) = '\0';
        *buf_size = len + 1;
        return 1;
    }

    if (!strcmp(variable_name, "ALL_RAW"))
    {
        /* crlf delimited, colon split, comma separated and
         * null terminated list of the raw request header
         */
        const apr_array_header_t *arr = apr_table_elts(r->headers_in);
        const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;
        int i;

        for (len = 0, i = 0; i < arr->nelts; i++) {
            len += strlen(elts[i].key) + strlen(elts[i].val) + 4;
        }

        if (*buf_size < len + 1) {
            *buf_size = len + 1;
            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INSUFFICIENT_BUFFER));
            return 0;
        }

        for (i = 0; i < arr->nelts; i++) {
            strcpy(buf_data, elts[i].key);
            buf_data += strlen(elts[i].key);
            *(buf_data++) = ':';
            *(buf_data++) = ' ';
            strcpy(buf_data, elts[i].val);
            buf_data += strlen(elts[i].val);
            *(buf_data++) = '\r';
            *(buf_data++) = '\n';
        }
        *(buf_data++) = '\0';
        *buf_size = len + 1;
        return 1;
    }

    /* Not a special case */
    result = apr_table_get(r->subprocess_env, variable_name);

    if (result) {
        len = strlen(result);
        if (*buf_size < len + 1) {
            *buf_size = len + 1;
            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INSUFFICIENT_BUFFER));
            return 0;
        }
        strcpy(buf_data, result);
        *buf_size = len + 1;
        return 1;
    }

    /* Not Found */
    apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_INDEX));
    return 0;
}