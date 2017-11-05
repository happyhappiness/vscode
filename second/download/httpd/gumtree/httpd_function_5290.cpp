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
    const unsigned char padlen = frame->data.padlen;
    int eos;
    h2_stream *stream;
    
    (void)ngh2;
    (void)source;
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    stream = h2_stream_set_get(session->streams, stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_NOTFOUND, session->c,
                      APLOGNO(02924) 
                      "h2_stream(%ld-%d): send_data",
                      session->id, (int)stream_id);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    status = send_data(session, (const char *)framehd, 9);
    if (status == APR_SUCCESS) {
        if (padlen) {
            status = send_data(session, (const char *)&padlen, 1);
        }

        if (status == APR_SUCCESS) {
            apr_size_t len = length;
            status = h2_stream_readx(stream, pass_data, session, 
                                     &len, &eos);
            if (status == APR_SUCCESS && len != length) {
                status = APR_EINVAL;
            }
        }
        
        if (status == APR_SUCCESS && padlen) {
            if (padlen) {
                char pad[256];
                memset(pad, 0, padlen);
                status = send_data(session, pad, padlen);
            }
        }
    }
    
    if (status == APR_SUCCESS) {
        return 0;
    }
    else if (status != APR_EOF) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                      APLOGNO(02925) 
                      "h2_stream(%ld-%d): failed send_data_cb",
                      session->id, (int)stream_id);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    return h2_session_status_from_apr_status(status);
}