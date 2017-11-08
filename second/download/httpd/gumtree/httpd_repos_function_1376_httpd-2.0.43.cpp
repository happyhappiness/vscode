int APR_THREAD_FUNC GetServerVariable (isapi_cid    *cid, 
                                       char         *variable_name,
                                       void         *buf_data, 
                                       apr_uint32_t *buf_size)
{
    request_rec *r = cid->r;
    const char *result;
    apr_uint32_t len;

    if (!strcmp(variable_name, "ALL_HTTP")) 
    {
        /* lf delimited, colon split, comma seperated and 
         * null terminated list of HTTP_ vars 
         */
        const apr_array_header_t *arr = apr_table_elts(r->subprocess_env);
        const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;
        int i;

        for (len = 0, i = 0; i < arr->nelts; i++) {
            if (!strncmp(elts[i].key, "HTTP_", 5)) {
                len += strlen(elts[i].key) + strlen(elts[i].val) + 2;
            }
        }
  
        if (*buf_size < len + 1) {
            *buf_size = len + 1;
            SetLastError(ERROR_INSUFFICIENT_BUFFER);
            return 0;
        }
    
        for (i = 0; i < arr->nelts; i++) {
            if (!strncmp(elts[i].key, "HTTP_", 5)) {
                strcpy(buf_data, elts[i].key);
                ((char*)buf_data) += strlen(elts[i].key);
                *(((char*)buf_data)++) = ':';
                strcpy(buf_data, elts[i].val);
                ((char*)buf_data) += strlen(elts[i].val);
                *(((char*)buf_data)++) = '\n';
            }
        }

        *(((char*)buf_data)++) = '\0';
        *buf_size = len + 1;
        return 1;
    }
    
    if (!strcmp(variable_name, "ALL_RAW")) 
    {
        /* lf delimited, colon split, comma seperated and 
         * null terminated list of the raw request header
         */
        const apr_array_header_t *arr = apr_table_elts(r->headers_in);
        const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;
        int i;

        for (len = 0, i = 0; i < arr->nelts; i++) {
            len += strlen(elts[i].key) + strlen(elts[i].val) + 2;
        }
  
        if (*buf_size < len + 1) {
            *buf_size = len + 1;
            SetLastError(ERROR_INSUFFICIENT_BUFFER);
            return 0;
        }
    
        for (i = 0; i < arr->nelts; i++) {
            strcpy(buf_data, elts[i].key);
            ((char*)buf_data) += strlen(elts[i].key);
            *(((char*)buf_data)++) = ':';
            *(((char*)buf_data)++) = ' ';
            strcpy(buf_data, elts[i].val);
            ((char*)buf_data) += strlen(elts[i].val);
            *(((char*)buf_data)++) = '\n';
        }
        *(((char*)buf_data)++) = '\0';
        *buf_size = len + 1;
        return 1;
    }
    
    /* Not a special case */
    result = apr_table_get(r->subprocess_env, variable_name);

    if (result) {
        len = strlen(result);
        if (*buf_size < len + 1) {
            *buf_size = len + 1;
            SetLastError(ERROR_INSUFFICIENT_BUFFER);
            return 0;
        }
        strcpy(buf_data, result);
        *buf_size = len + 1;
        return 1;
    }

    /* Not Found */
    SetLastError(ERROR_INVALID_INDEX);
    return 0;
}