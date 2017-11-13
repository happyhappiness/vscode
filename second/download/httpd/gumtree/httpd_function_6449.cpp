apr_status_t h2_stream_write_data(h2_stream *stream,
                                  const char *data, size_t len, int eos)
{
    apr_status_t status = APR_SUCCESS;
    
    AP_DEBUG_ASSERT(stream);
    if (input_closed(stream) || !stream->request->eoh) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      "h2_stream(%ld-%d): writing denied, closed=%d, eoh=%d", 
                      stream->session->id, stream->id, input_closed(stream),
                      stream->request->eoh);
        return APR_EINVAL;
    }

    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                  "h2_stream(%ld-%d): add %ld input bytes", 
                  stream->session->id, stream->id, (long)len);

    if (!stream->request->chunked) {
        stream->input_remaining -= len;
        if (stream->input_remaining < 0) {
            ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, stream->session->c,
                          APLOGNO(02961) 
                          "h2_stream(%ld-%d): got %ld more content bytes than announced "
                          "in content-length header: %ld", 
                          stream->session->id, stream->id,
                          (long)stream->request->content_length, 
                          -(long)stream->input_remaining);
            h2_stream_rst(stream, H2_ERR_PROTOCOL_ERROR);
            return APR_ECONNABORTED;
        }
    }
    
    status = h2_mplx_in_write(stream->session->mplx, stream->id, data, len, eos);
    if (eos) {
        close_input(stream);
    }
    return status;
}