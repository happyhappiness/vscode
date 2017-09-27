        return APR_EINVAL;
    }
    if (eos) {
        close_input(stream);
    }
    
    if (stream->response) {
        /* already have a resonse, probably a HTTP error code */
        return h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
    }
    
    /* Seeing the end-of-headers, we have everything we need to 
     * start processing it.
     */
    status = h2_request_end_headers(stream->request, stream->pool, 
                                    eos, push_enabled);
    if (status == APR_SUCCESS) {
        stream->request->body = !eos;
        stream->scheduled = 1;
        stream->input_remaining = stream->request->content_length;
        
        status = h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      "h2_stream(%ld-%d): scheduled %s %s://%s%s",
                      stream->session->id, stream->id,
                      stream->request->method, stream->request->scheme,
                      stream->request->authority, stream->request->path);
    }
    else {
        h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                      "h2_stream(%ld-%d): RST=2 (internal err) %s %s://%s%s",
                      stream->session->id, stream->id,
                      stream->request->method, stream->request->scheme,
                      stream->request->authority, stream->request->path);
    }
    
