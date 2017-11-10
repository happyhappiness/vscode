static int on_send_data_cb(nghttp2_session *ngh2, 
                           nghttp2_frame *frame, 
                           const uint8_t *framehd, 
                           size_t length, 
                           nghttp2_data_source *source, 
                           void *userp)
{
    apr_status_t status = APR_SUCCESS;
    h2_session *session = (h2_session *)userp;
    int stream_id = (int)frame->hd.stream_id;
    unsigned char padlen;
    int eos;
    h2_stream *stream;
    
    (void)ngh2;
    (void)source;
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    if (frame->data.padlen > H2_MAX_PADLEN) {
        return NGHTTP2_ERR_PROTO;
    }
    padlen = (unsigned char)frame->data.padlen;
    
    stream = h2_session_get_stream(session, stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_NOTFOUND, session->c,
                      APLOGNO(02924) 
                      "h2_stream(%ld-%d): send_data",
                      session->id, (int)stream_id);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_stream(%ld-%d): send_data_cb for %ld bytes",
                  session->id, (int)stream_id, (long)length);
                  
    if (h2_conn_io_is_buffered(&session->io)) {
        status = h2_conn_io_write(&session->io, (const char *)framehd, 9);
        if (status == APR_SUCCESS) {
            if (padlen) {
                status = h2_conn_io_write(&session->io, (const char *)&padlen, 1);
            }
            
            if (status == APR_SUCCESS) {
                apr_off_t len = length;
                status = h2_stream_readx(stream, pass_data, session, &len, &eos);
                if (status == APR_SUCCESS && len != length) {
                    status = APR_EINVAL;
                }
            }
            
            if (status == APR_SUCCESS && padlen) {
                if (padlen) {
                    status = h2_conn_io_write(&session->io, immortal_zeros, padlen);
                }
            }
        }
    }
    else {
        apr_bucket *b;
        char *header = apr_pcalloc(stream->pool, 10);
        memcpy(header, (const char *)framehd, 9);
        if (padlen) {
            header[9] = (char)padlen;
        }
        b = apr_bucket_pool_create(header, padlen? 10 : 9, 
                                   stream->pool, session->c->bucket_alloc);
        status = h2_conn_io_writeb(&session->io, b);
        
        if (status == APR_SUCCESS) {
            apr_off_t len = length;
            status = h2_stream_read_to(stream, session->io.output, &len, &eos);
            if (status == APR_SUCCESS && len != length) {
                status = APR_EINVAL;
            }
        }
            
        if (status == APR_SUCCESS && padlen) {
            b = apr_bucket_immortal_create(immortal_zeros, padlen, 
                                           session->c->bucket_alloc);
            status = h2_conn_io_writeb(&session->io, b);
        }
    }
    
    
    if (status == APR_SUCCESS) {
        stream->data_frames_sent++;
        h2_conn_io_consider_flush(&session->io);
        return 0;
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                      APLOGNO(02925) 
                      "h2_stream(%ld-%d): failed send_data_cb",
                      session->id, (int)stream_id);
    }
    
    return h2_session_status_from_apr_status(status);
}