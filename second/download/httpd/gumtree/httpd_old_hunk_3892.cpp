}

static int on_data_chunk_recv_cb(nghttp2_session *ngh2, uint8_t flags,
                                 int32_t stream_id,
                                 const uint8_t *data, size_t len, void *userp)
{
    int rv;
    h2_session *session = (h2_session *)userp;
    h2_stream * stream;
    apr_status_t status;
    
    (void)flags;
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    stream = h2_stream_set_get(session->streams, stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                      APLOGNO(02919) 
                      "h2_session:  stream(%ld-%d): on_data_chunk for unknown stream",
                      session->id, (int)stream_id);
        rv = nghttp2_submit_rst_stream(ngh2, NGHTTP2_FLAG_NONE, stream_id,
                                       NGHTTP2_INTERNAL_ERROR);
        if (nghttp2_is_fatal(rv)) {
            return NGHTTP2_ERR_CALLBACK_FAILURE;
        }
        return 0;
    }
    
    status = h2_stream_write_data(stream, (const char *)data, len);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c,
                  "h2_stream(%ld-%d): written DATA, length %d",
                  session->id, stream_id, (int)len);
    if (status != APR_SUCCESS) {
        rv = nghttp2_submit_rst_stream(ngh2, NGHTTP2_FLAG_NONE, stream_id,
                                       NGHTTP2_INTERNAL_ERROR);
        if (nghttp2_is_fatal(rv)) {
            return NGHTTP2_ERR_CALLBACK_FAILURE;
        }
    }
    return 0;
}

static int before_frame_send_cb(nghttp2_session *ngh2,
                                const nghttp2_frame *frame,
                                void *userp)
{
    h2_session *session = (h2_session *)userp;
    (void)ngh2;

    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    if (APLOGctrace2(session->c)) {
        char buffer[256];
        frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_session(%ld): before_frame_send %s", 
                      session->id, buffer);
    }
    return 0;
}

static int on_frame_send_cb(nghttp2_session *ngh2,
                            const nghttp2_frame *frame,
                            void *userp)
{
    h2_session *session = (h2_session *)userp;
    (void)ngh2; (void)frame;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_session(%ld): on_frame_send", session->id);
    return 0;
}

static int on_frame_not_send_cb(nghttp2_session *ngh2,
                                const nghttp2_frame *frame,
                                int lib_error_code, void *userp)
{
    h2_session *session = (h2_session *)userp;
    (void)ngh2;
    
    if (APLOGctrace2(session->c)) {
        char buffer[256];
        
        frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_session: callback on_frame_not_send error=%d %s",
                      lib_error_code, buffer);
    }
    return 0;
}

static apr_status_t stream_destroy(h2_session *session, 
                                   h2_stream *stream,
                                   uint32_t error_code) 
{
    if (!error_code) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): handled, closing", 
