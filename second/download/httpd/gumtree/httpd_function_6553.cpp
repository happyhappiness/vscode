static apr_status_t get_line(h2_from_h1 *from_h1, apr_bucket_brigade *bb,
                             ap_filter_t* f, char *line, apr_size_t len)
{
    apr_status_t status;
    if (!from_h1->bb) {
        from_h1->bb = apr_brigade_create(from_h1->pool, f->c->bucket_alloc);
    }
    else {
        apr_brigade_cleanup(from_h1->bb);                
    }
    status = apr_brigade_split_line(from_h1->bb, bb, 
                                                 APR_BLOCK_READ, 
                                                 HUGE_STRING_LEN);
    if (status == APR_SUCCESS) {
        --len;
        status = apr_brigade_flatten(from_h1->bb, line, &len);
        if (status == APR_SUCCESS) {
            /* we assume a non-0 containing line and remove
             * trailing crlf. */
            line[len] = '\0';
            if (len >= 2 && !strcmp(H2_CRLF, line + len - 2)) {
                len -= 2;
                line[len] = '\0';
            }
            
            apr_brigade_cleanup(from_h1->bb);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                          "h2_from_h1(%d): read line: %s",
                          from_h1->stream_id, line);
        }
    }
    return status;
}