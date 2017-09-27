        close_input(stream);
    }
    
    /* Seeing the end-of-headers, we have everything we need to 
     * start processing it.
     */
    status = h2_request_end_headers(stream->request, stream->pool, 
                                    eos, push_enabled);
    if (status == APR_SUCCESS) {
        if (!eos) {
            stream->request->body = 1;
        }
        stream->input_remaining = stream->request->content_length;
        
        status = h2_mplx_process(stream->session->mplx, stream->id, 
                                 stream->request, cmp, ctx);
        stream->scheduled = 1;
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      "h2_stream(%ld-%d): scheduled %s %s://%s%s",
                      stream->session->id, stream->id,
                      stream->request->method, stream->request->scheme,
                      stream->request->authority, stream->request->path);
    }
    else {
        h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      "h2_stream(%ld-%d): RST=2 (internal err) %s %s://%s%s",
                      stream->session->id, stream->id,
                      stream->request->method, stream->request->scheme,
                      stream->request->authority, stream->request->path);
    }
    
    return status;
}

int h2_stream_is_scheduled(const h2_stream *stream)
{
    return stream->scheduled;
}

apr_status_t h2_stream_close_input(h2_stream *stream)
{
    apr_status_t status = APR_SUCCESS;
    
    AP_DEBUG_ASSERT(stream);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                  "h2_stream(%ld-%d): closing input",
                  stream->session->id, stream->id);
                  
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    
    if (close_input(stream)) {
        status = h2_mplx_in_close(stream->session->mplx, stream->id);
    }
    return status;
}

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

void h2_stream_set_suspended(h2_stream *stream, int suspended)
{
    AP_DEBUG_ASSERT(stream);
    stream->suspended = !!suspended;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c,
                  "h2_stream(%ld-%d): suspended=%d",
                  stream->session->id, stream->id, stream->suspended);
}

int h2_stream_is_suspended(const h2_stream *stream)
{
    AP_DEBUG_ASSERT(stream);
    return stream->suspended;
}

apr_status_t h2_stream_out_prepare(h2_stream *stream, 
                                   apr_off_t *plen, int *peos)
{
    if (stream->rst_error) {
        *plen = 0;
        *peos = 1;
        return APR_ECONNRESET;
    }

    AP_DEBUG_ASSERT(stream->sos);
    return stream->sos->prepare(stream->sos, plen, peos);
}

apr_status_t h2_stream_readx(h2_stream *stream, 
                             h2_io_data_cb *cb, void *ctx,
                             apr_off_t *plen, int *peos)
{
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    if (!stream->sos) {
        return APR_EGENERAL;
    }
    return stream->sos->readx(stream->sos, cb, ctx, plen, peos);
}

apr_status_t h2_stream_read_to(h2_stream *stream, apr_bucket_brigade *bb, 
                               apr_off_t *plen, int *peos)
{
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    if (!stream->sos) {
        return APR_EGENERAL;
    }
    return stream->sos->read_to(stream->sos, bb, plen, peos);
}

int h2_stream_input_is_open(const h2_stream *stream) 
{
    return input_open(stream);
}

int h2_stream_needs_submit(const h2_stream *stream)
{
    switch (stream->state) {
        case H2_STREAM_ST_OPEN:
        case H2_STREAM_ST_CLOSED_INPUT:
        case H2_STREAM_ST_CLOSED_OUTPUT:
        case H2_STREAM_ST_CLOSED:
