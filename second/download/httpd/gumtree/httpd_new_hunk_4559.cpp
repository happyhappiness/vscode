    apr_off_t len = 0;
    int eos = 0;
    h2_headers *headers;
    
    ap_assert(stream);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                  H2_STRM_MSG(stream, "on_resume"));
    
send_headers:
    headers = NULL;
    status = h2_stream_out_prepare(stream, &len, &eos, &headers);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, session->c, 
                  H2_STRM_MSG(stream, "prepared len=%ld, eos=%d"), 
                  (long)len, eos);
    if (headers) {
        status = on_stream_headers(session, stream, headers, len, eos);
        if (status != APR_SUCCESS || stream->rst_error) {
            return status;
        }
        goto send_headers;
    }
    else if (status != APR_EAGAIN) {
        /* we have DATA to send */
        if (!stream->has_response) {
            /* but no response */
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                          H2_STRM_LOG(APLOGNO(03466), stream, 
                          "no response, RST_STREAM"));
            h2_stream_rst(stream, H2_ERR_PROTOCOL_ERROR);
            return APR_SUCCESS;
        } 
        rv = nghttp2_session_resume_data(session->ngh2, stream->id);
        session->have_written = 1;
        ap_log_cerror(APLOG_MARK, nghttp2_is_fatal(rv)?
                      APLOG_ERR : APLOG_DEBUG, 0, session->c,  
                      H2_STRM_LOG(APLOGNO(02936), stream, "resumed"));
    }
    return status;
}

static void h2_session_in_flush(h2_session *session)
{
    int id;
    
    while ((id = h2_iq_shift(session->in_process)) > 0) {
        h2_stream *stream = h2_session_stream_get(session, id);
        if (stream) {
            ap_assert(!stream->scheduled);
            if (h2_stream_prep_processing(stream) == APR_SUCCESS) {
                h2_mplx_process(session->mplx, stream, stream_pri_cmp, session);
            }
            else {
                h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
            }
        }
    }

    while ((id = h2_iq_shift(session->in_pending)) > 0) {
        h2_stream *stream = h2_session_stream_get(session, id);
        if (stream) {
            h2_stream_flush_input(stream);
        }
    }
}

static apr_status_t session_read(h2_session *session, apr_size_t readlen, int block)
{
    apr_status_t status, rstatus = APR_EAGAIN;
    conn_rec *c = session->c;
    apr_off_t read_start = session->io.bytes_read;
    
    while (1) {
        /* H2_IN filter handles all incoming data against the session.
         * We just pull at the filter chain to make it happen */
        status = ap_get_brigade(c->input_filters,
                                session->bbtmp, AP_MODE_READBYTES,
                                block? APR_BLOCK_READ : APR_NONBLOCK_READ,
                                H2MAX(APR_BUCKET_BUFF_SIZE, readlen));
        /* get rid of any possible data we do not expect to get */
        apr_brigade_cleanup(session->bbtmp); 

        switch (status) {
            case APR_SUCCESS:
                /* successful read, reset our idle timers */
