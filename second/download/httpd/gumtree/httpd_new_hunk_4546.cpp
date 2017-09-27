    h2_stream *stream;
    apr_bucket *b;
    apr_off_t len = length;
    
    (void)ngh2;
    (void)source;
    if (!h2_session_continue_data(session)) {
        return NGHTTP2_ERR_WOULDBLOCK;
    }

    if (frame->data.padlen > H2_MAX_PADLEN) {
        return NGHTTP2_ERR_PROTO;
    }
    padlen = (unsigned char)frame->data.padlen;
    
    stream = h2_session_stream_get(session, stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_NOTFOUND, session->c,
                      APLOGNO(02924) 
                      "h2_stream(%ld-%d): send_data, stream not found",
                      session->id, (int)stream_id);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  H2_STRM_MSG(stream, "send_data_cb for %ld bytes"),
                  (long)length);
                  
    status = h2_conn_io_write(&session->io, (const char *)framehd, 9);
    if (padlen && status == APR_SUCCESS) {
        status = h2_conn_io_write(&session->io, (const char *)&padlen, 1);
    }
    
    if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c,
                      H2_STRM_MSG(stream, "writing frame header"));
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    status = h2_stream_read_to(stream, session->bbtmp, &len, &eos);
    if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c,
                      H2_STRM_MSG(stream, "send_data_cb, reading stream"));
        apr_brigade_cleanup(session->bbtmp);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    else if (len != length) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c,
                      H2_STRM_MSG(stream, "send_data_cb, wanted %ld bytes, "
                      "got %ld from stream"), (long)length, (long)len);
        apr_brigade_cleanup(session->bbtmp);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    if (padlen) {
        b = apr_bucket_immortal_create(immortal_zeros, padlen, 
