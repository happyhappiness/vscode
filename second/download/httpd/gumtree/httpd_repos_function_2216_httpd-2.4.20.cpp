static void check_clen(h2_response *response, request_rec *r, apr_pool_t *pool)
{
    
    if (r && r->header_only) {
        response->content_length = 0;
    }
    else if (response->headers) {
        const char *s = apr_table_get(response->headers, "Content-Length");
        if (s) {
            char *end;
            response->content_length = apr_strtoi64(s, &end, 10);
            if (s == end) {
                ap_log_perror(APLOG_MARK, APLOG_WARNING, APR_EINVAL, 
                              pool, APLOGNO(02956) 
                              "h2_response: content-length"
                              " value not parsed: %s", s);
                response->content_length = -1;
            }
        }
    }
}