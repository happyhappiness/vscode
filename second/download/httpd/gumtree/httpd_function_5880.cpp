apr_status_t h2_stream_write_data(h2_stream *stream,
                                  const char *data, size_t len)
{
    apr_status_t status = APR_SUCCESS;
    
    AP_DEBUG_ASSERT(stream);
    if (input_closed(stream) || !stream->request->eoh || !stream->bbin) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
                      "h2_stream(%ld-%d): writing denied, closed=%d, eoh=%d, bbin=%d", 
                      stream->session->id, stream->id, input_closed(stream),
                      stream->request->eoh, !!stream->bbin);
        return APR_EINVAL;
    }

    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
                  "h2_stream(%ld-%d): add %ld input bytes", 
                  stream->session->id, stream->id, (long)len);

    H2_STREAM_IN(APLOG_TRACE2, stream, "write_data_pre");
    if (stream->request->chunked) {
        /* if input may have a body and we have not seen any
         * content-length header, we need to chunk the input data.
         */
        status = input_add_data(stream, data, len, 1);
    }
    else {
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
        status = input_add_data(stream, data, len, 0);
    }
    if (status == APR_SUCCESS) {
        status = h2_stream_input_flush(stream);
    }
    H2_STREAM_IN(APLOG_TRACE2, stream, "write_data_post");
    return status;
}