apr_status_t h2_from_h1_read_response(h2_from_h1 *from_h1, ap_filter_t* f,
                                      apr_bucket_brigade* bb)
{
    apr_status_t status = APR_SUCCESS;
    char line[HUGE_STRING_LEN];
    
    if ((from_h1->state == H2_RESP_ST_BODY) 
        || (from_h1->state == H2_RESP_ST_DONE)) {
        if (from_h1->chunked) {
            /* The httpd core HTTP_HEADER filter has or will install the 
             * "CHUNK" output transcode filter, which appears further down 
             * the filter chain. We do not want it for HTTP/2.
             * Once we successfully deinstalled it, this filter has no
             * further function and we remove it.
             */
            status = ap_remove_output_filter_byhandle(f->r->output_filters, 
                                                      "CHUNK");
            if (status == APR_SUCCESS) {
                ap_remove_output_filter(f);
            }
        }
        
        return ap_pass_brigade(f->next, bb);
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                  "h2_from_h1(%d): read_response", from_h1->stream_id);
    
    while (!APR_BRIGADE_EMPTY(bb) && status == APR_SUCCESS) {
        
        switch (from_h1->state) {
                
            case H2_RESP_ST_STATUS_LINE:
            case H2_RESP_ST_HEADERS:
                status = get_line(from_h1, bb, f, line, sizeof(line));
                if (status != APR_SUCCESS) {
                    return status;
                }
                if (from_h1->state == H2_RESP_ST_STATUS_LINE) {
                    /* instead of parsing, just take it directly */
                    from_h1->http_status = f->r->status;
                    from_h1->state = H2_RESP_ST_HEADERS;
                }
                else if (line[0] == '\0') {
                    /* end of headers, create the h2_response and
                     * pass the rest of the brigade down the filter
                     * chain.
                     */
                    status = make_h2_headers(from_h1, f->r);
                    if (from_h1->bb) {
                        apr_brigade_destroy(from_h1->bb);
                        from_h1->bb = NULL;
                    }
                    if (!APR_BRIGADE_EMPTY(bb)) {
                        return ap_pass_brigade(f->next, bb);
                    }
                }
                else {
                    status = parse_header(from_h1, f, line);
                }
                break;
                
            default:
                return ap_pass_brigade(f->next, bb);
        }
        
    }
    
    return status;
}