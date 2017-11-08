static apr_status_t serialize_table(cache_header_tbl_t **obj, 
                                    apr_ssize_t *nelts, 
                                    apr_table_t *table)
{
    const apr_array_header_t *elts_arr = apr_table_elts(table);
    apr_table_entry_t *elts = (apr_table_entry_t *) elts_arr->elts;
    apr_ssize_t i;
    apr_size_t len = 0;
    apr_size_t idx = 0;
    char *buf;
   
    *nelts = elts_arr->nelts;
    if (*nelts == 0 ) {
        *obj=NULL;
        return APR_SUCCESS;
    }
    *obj = malloc(sizeof(cache_header_tbl_t) * elts_arr->nelts);
    if (NULL == *obj) {
        return APR_ENOMEM;
    }
    for (i = 0; i < elts_arr->nelts; ++i) {
        len += strlen(elts[i].key);
        len += strlen(elts[i].val);
        len += 2;  /* Extra space for NULL string terminator for key and val */
    }

    /* Transfer the headers into a contiguous memory block */
    buf = malloc(len);
    if (!buf) {
        *obj = NULL;
        return APR_ENOMEM;
    }

    for (i = 0; i < *nelts; ++i) {
        (*obj)[i].hdr = &buf[idx];
        len = strlen(elts[i].key) + 1;              /* Include NULL terminator */
        memcpy(&buf[idx], elts[i].key, len);
        idx+=len;

        (*obj)[i].val = &buf[idx];
        len = strlen(elts[i].val) + 1;
        memcpy(&buf[idx], elts[i].val, len);
        idx+=len;
    }
    return APR_SUCCESS;
}