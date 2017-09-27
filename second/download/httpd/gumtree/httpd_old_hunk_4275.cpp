                  "h2_stream(%ld-%d): reset, error=%d", 
                  stream->session->id, stream->id, error_code);
}

struct h2_response *h2_stream_get_response(h2_stream *stream)
{
    return stream->sos? stream->sos->response : NULL;
}

apr_status_t h2_stream_set_response(h2_stream *stream, h2_response *response,
                                    apr_bucket_brigade *bb)
{
    apr_status_t status = APR_SUCCESS;
    h2_sos *sos;
    
    if (!output_open(stream)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      "h2_stream(%ld-%d): output closed", 
                      stream->session->id, stream->id);
        return APR_ECONNRESET;
    }
    
    sos = h2_sos_mplx_create(stream, response);
    if (sos->response->sos_filter) {
        sos = h2_filter_sos_create(sos->response->sos_filter, sos); 
    }
    stream->sos = sos;
    
    status = stream->sos->buffer(stream->sos, bb);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                  "h2_stream(%ld-%d): set_response(%d)", 
                  stream->session->id, stream->id, stream->sos->response->http_status);
    return status;
}

apr_status_t h2_stream_set_request(h2_stream *stream, request_rec *r)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(stream);
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    set_state(stream, H2_STREAM_ST_OPEN);
    status = h2_request_rwrite(stream->request, r);
    stream->request->serialize = h2_config_geti(h2_config_rget(r), 
                                                H2_CONF_SER_HEADERS);

    return status;
}

void h2_stream_set_h2_request(h2_stream *stream, int initiated_on,
                              const h2_request *req)
{
    h2_request_copy(stream->pool, stream->request, req);
    stream->request->initiated_on = initiated_on;
    stream->request->eoh = 0;
}

apr_status_t h2_stream_add_header(h2_stream *stream,
                                  const char *name, size_t nlen,
                                  const char *value, size_t vlen)
{
    AP_DEBUG_ASSERT(stream);
    if (h2_stream_is_scheduled(stream)) {
        return h2_request_add_trailer(stream->request, stream->pool,
                                      name, nlen, value, vlen);
    }
    else {
        if (!input_open(stream)) {
