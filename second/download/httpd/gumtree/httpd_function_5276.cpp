h2_response *h2_response_create(int stream_id,
                                const char *http_status,
                                apr_array_header_t *hlines,
                                apr_pool_t *pool)
{
    apr_table_t *header;
    h2_response *response = apr_pcalloc(pool, sizeof(h2_response));
    int i;
    if (response == NULL) {
        return NULL;
    }
    
    response->stream_id = stream_id;
    response->status = http_status;
    response->content_length = -1;
    
    if (hlines) {
        header = apr_table_make(pool, hlines->nelts);        
        for (i = 0; i < hlines->nelts; ++i) {
            char *hline = ((char **)hlines->elts)[i];
            char *sep = ap_strchr(hline, ':');
            if (!sep) {
                ap_log_perror(APLOG_MARK, APLOG_WARNING, APR_EINVAL, pool,
                              APLOGNO(02955) "h2_response(%d): invalid header[%d] '%s'",
                              response->stream_id, i, (char*)hline);
                /* not valid format, abort */
                return NULL;
            }
            (*sep++) = '\0';
            while (*sep == ' ' || *sep == '\t') {
                ++sep;
            }
            if (ignore_header(hline)) {
                /* never forward, ch. 8.1.2.2 */
            }
            else {
                apr_table_merge(header, hline, sep);
                if (*sep && H2_HD_MATCH_LIT_CS("content-length", hline)) {
                    char *end;
                    response->content_length = apr_strtoi64(sep, &end, 10);
                    if (sep == end) {
                        ap_log_perror(APLOG_MARK, APLOG_WARNING, APR_EINVAL, 
                                      pool, APLOGNO(02956) 
                                      "h2_response(%d): content-length"
                                      " value not parsed: %s", 
                                      response->stream_id, sep);
                        response->content_length = -1;
                    }
                }
            }
        }
    }
    else {
        header = apr_table_make(pool, 0);        
    }

    response->rheader = header;
    return response;
}