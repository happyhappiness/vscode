                  "h2_stream(%ld-%d): reset, error=%d", 
                  stream->session->id, stream->id, error_code);
}

struct h2_response *h2_stream_get_response(h2_stream *stream)
{
    return stream->response;
}

apr_status_t h2_stream_set_request(h2_stream *stream, request_rec *r)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(stream);
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    set_state(stream, H2_STREAM_ST_OPEN);
    status = h2_request_rwrite(stream->request, stream->pool, r);
    stream->request->serialize = h2_config_geti(h2_config_rget(r), 
                                                H2_CONF_SER_HEADERS);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(03058)
                  "h2_request(%d): rwrite %s host=%s://%s%s",
                  stream->request->id, stream->request->method, 
                  stream->request->scheme, stream->request->authority, 
                  stream->request->path);

    return status;
}

apr_status_t h2_stream_add_header(h2_stream *stream,
                                  const char *name, size_t nlen,
                                  const char *value, size_t vlen)
{
    AP_DEBUG_ASSERT(stream);
    if (!stream->response) {
        if (name[0] == ':') {
            if ((vlen) > stream->session->s->limit_req_line) {
                /* pseudo header: approximation of request line size check */
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                              "h2_stream(%ld-%d): pseudo header %s too long", 
                              stream->session->id, stream->id, name);
                return h2_stream_set_error(stream, 
                                           HTTP_REQUEST_URI_TOO_LARGE);
            }
        }
        else if ((nlen + 2 + vlen) > stream->session->s->limit_req_fieldsize) {
            /* header too long */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                          "h2_stream(%ld-%d): header %s too long", 
                          stream->session->id, stream->id, name);
            return h2_stream_set_error(stream, 
                                       HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE);
        }
        
        if (name[0] != ':') {
            ++stream->request_headers_added;
            if (stream->request_headers_added 
                > stream->session->s->limit_req_fields) {
                /* too many header lines */
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                              "h2_stream(%ld-%d): too many header lines", 
                              stream->session->id, stream->id);
                return h2_stream_set_error(stream, 
                                           HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE);
            }
        }
    }
    
    if (h2_stream_is_scheduled(stream)) {
        return h2_request_add_trailer(stream->request, stream->pool,
                                      name, nlen, value, vlen);
    }
    else {
        if (!input_open(stream)) {
