static apr_table_t *parse_headers(apr_array_header_t *hlines, apr_pool_t *pool)
{
    if (hlines) {
        apr_table_t *headers = apr_table_make(pool, hlines->nelts);        
        int i;
        
        for (i = 0; i < hlines->nelts; ++i) {
            char *hline = ((char **)hlines->elts)[i];
            char *sep = ap_strchr(hline, ':');
            if (!sep) {
                ap_log_perror(APLOG_MARK, APLOG_WARNING, APR_EINVAL, pool,
                              APLOGNO(02955) "h2_response: invalid header[%d] '%s'",
                              i, (char*)hline);
                /* not valid format, abort */
                return NULL;
            }
            (*sep++) = '\0';
            while (*sep == ' ' || *sep == '\t') {
                ++sep;
            }
            
            if (!h2_util_ignore_header(hline)) {
                apr_table_merge(headers, hline, sep);
            }
        }
        return headers;
    }
    else {
        return apr_table_make(pool, 0);        
    }
}