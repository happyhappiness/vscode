apr_status_t h2_stream_set_response(h2_stream *stream, h2_response *response,
                                    h2_bucket_beam *output)
{
    apr_status_t status = APR_SUCCESS;
    conn_rec *c = stream->session->c;
    
    if (!output_open(stream)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      "h2_stream(%ld-%d): output closed", 
                      stream->session->id, stream->id);
        return APR_ECONNRESET;
    }
    
    stream->response = response;
    stream->output = output;
    stream->buffer = apr_brigade_create(stream->pool, c->bucket_alloc);
    
    h2_stream_filter(stream);
    if (stream->output) {
        status = fill_buffer(stream, 0);
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c,
                  "h2_stream(%ld-%d): set_response(%d)", 
                  stream->session->id, stream->id, 
                  stream->response->http_status);
    return status;
}