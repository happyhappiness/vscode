    (void)ngh2;
    
    if (APLOGcdebug(session->c)) {
        char buffer[256];
        
        h2_util_frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03063)
                      "h2_session(%ld): recv invalid FRAME[%s], frames=%ld/%ld (r/s)",
                      session->id, buffer, (long)session->frames_received,
                     (long)session->frames_sent);
    }
    return 0;
}

static h2_stream *get_stream(h2_session *session, int stream_id)
{
    return nghttp2_session_get_stream_user_data(session->ngh2, stream_id);
}

static int on_data_chunk_recv_cb(nghttp2_session *ngh2, uint8_t flags,
                                 int32_t stream_id,
                                 const uint8_t *data, size_t len, void *userp)
{
    h2_session *session = (h2_session *)userp;
    apr_status_t status = APR_SUCCESS;
    h2_stream * stream;
    int rv;
    
    (void)flags;
    stream = get_stream(session, stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03064)
                      "h2_stream(%ld-%d): on_data_chunk for unknown stream",
                      session->id, (int)stream_id);
        rv = nghttp2_submit_rst_stream(ngh2, NGHTTP2_FLAG_NONE, stream_id,
                                       NGHTTP2_INTERNAL_ERROR);
        if (nghttp2_is_fatal(rv)) {
            return NGHTTP2_ERR_CALLBACK_FAILURE;
        }
        return 0;
    }

    /* FIXME: enabling setting EOS this way seems to break input handling
     * in mod_proxy_http2. why? */
    status = h2_stream_write_data(stream, (const char *)data, len,
                                  0 /*flags & NGHTTP2_FLAG_END_STREAM*/);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c,
                  "h2_stream(%ld-%d): data_chunk_recv, written %ld bytes",
                  session->id, stream_id, (long)len);
    if (status != APR_SUCCESS) {
        update_window(session, stream_id, len);
        rv = nghttp2_submit_rst_stream(ngh2, NGHTTP2_FLAG_NONE, stream_id,
                                       H2_STREAM_RST(stream, H2_ERR_INTERNAL_ERROR));
        if (nghttp2_is_fatal(rv)) {
            return NGHTTP2_ERR_CALLBACK_FAILURE;
        }
    }
    return 0;
}

static apr_status_t stream_release(h2_session *session, 
                                   h2_stream *stream,
                                   uint32_t error_code) 
{
    conn_rec *c = session->c;
    apr_bucket *b;
    apr_status_t status;
    
    if (!error_code) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      "h2_stream(%ld-%d): handled, closing", 
                      session->id, (int)stream->id);
        if (H2_STREAM_CLIENT_INITIATED(stream->id)) {
            if (stream->id > session->local.completed_max) {
                session->local.completed_max = stream->id;
            }
        }
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03065)
                      "h2_stream(%ld-%d): closing with err=%d %s", 
                      session->id, (int)stream->id, (int)error_code,
                      h2_h2_err_description(error_code));
        h2_stream_rst(stream, error_code);
    }
    
    b = h2_bucket_eos_create(c->bucket_alloc, stream);
    APR_BRIGADE_INSERT_TAIL(session->bbtmp, b);
    status = h2_conn_io_pass(&session->io, session->bbtmp);
    apr_brigade_cleanup(session->bbtmp);
    return status;
}

static int on_stream_close_cb(nghttp2_session *ngh2, int32_t stream_id,
                              uint32_t error_code, void *userp)
{
    h2_session *session = (h2_session *)userp;
    h2_stream *stream;
    
    (void)ngh2;
    stream = get_stream(session, stream_id);
    if (stream) {
        stream_release(session, stream, error_code);
    }
    return 0;
}

static int on_begin_headers_cb(nghttp2_session *ngh2,
                               const nghttp2_frame *frame, void *userp)
