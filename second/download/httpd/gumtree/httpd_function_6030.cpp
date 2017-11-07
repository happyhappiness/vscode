apr_status_t h2_stream_write_data(h2_stream *stream,
                                  const char *data, size_t len, int eos)
{
    conn_rec *c = stream->session->c;
    apr_status_t status = APR_SUCCESS;
    
    AP_DEBUG_ASSERT(stream);
    if (!stream->input) {
        return APR_EOF;
    }
    if (input_closed(stream) || !stream->request->eoh) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      "h2_stream(%ld-%d): writing denied, closed=%d, eoh=%d", 
                      stream->session->id, stream->id, input_closed(stream),
                      stream->request->eoh);
        return APR_EINVAL;
    }

    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                  "h2_stream(%ld-%d): add %ld input bytes", 
                  stream->session->id, stream->id, (long)len);

    if (!stream->request->chunked) {
        stream->input_remaining -= len;
        if (stream->input_remaining < 0) {
            ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c,
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
    
    if (!stream->tmp) {
        stream->tmp = apr_brigade_create(stream->pool, c->bucket_alloc);
    }
    apr_brigade_write(stream->tmp, NULL, NULL, data, len);
    if (eos) {
        APR_BRIGADE_INSERT_TAIL(stream->tmp, 
                                apr_bucket_eos_create(c->bucket_alloc)); 
        close_input(stream);
    }
    
    status = h2_beam_send(stream->input, stream->tmp, APR_BLOCK_READ);
    apr_brigade_cleanup(stream->tmp);
    return status;
}