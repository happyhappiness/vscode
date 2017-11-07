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