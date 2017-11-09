static apr_status_t h2_proxy_stream_add_header_out(h2_proxy_stream *stream,
                                                   const char *n, apr_size_t nlen,
                                                   const char *v, apr_size_t vlen)
{
    if (n[0] == ':') {
        if (!stream->data_received && !strncmp(":status", n, nlen)) {
            char *s = apr_pstrndup(stream->r->pool, v, vlen);
            
            apr_table_setn(stream->r->notes, "proxy-status", s);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c, 
                          "h2_proxy_stream(%s-%d): got status %s", 
                          stream->session->id, stream->id, s);
            stream->r->status = (int)apr_atoi64(s);
            if (stream->r->status <= 0) {
                stream->r->status = 500;
                return APR_EGENERAL;
            }
        }
        return APR_SUCCESS;
    }
    
    if (!h2_proxy_res_ignore_header(n, nlen)) {
        char *hname, *hvalue;
    
        hname = apr_pstrndup(stream->pool, n, nlen);
        h2_proxy_util_camel_case_header(hname, nlen);
        hvalue = apr_pstrndup(stream->pool, v, vlen);
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c, 
                      "h2_proxy_stream(%s-%d): got header %s: %s", 
                      stream->session->id, stream->id, hname, hvalue);
        process_proxy_header(stream, hname, hvalue);
    }
    return APR_SUCCESS;
}