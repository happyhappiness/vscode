}

static apr_status_t stream_release(h2_session *session, 
                                   h2_stream *stream,
                                   uint32_t error_code) 
{
    if (!error_code) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                      "h2_stream(%ld-%d): handled, closing", 
                      session->id, (int)stream->id);
        if (H2_STREAM_CLIENT_INITIATED(stream->id)) {
            if (stream->id > session->local.completed_max) {
                session->local.completed_max = stream->id;
            }
        }
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03065)
                      "h2_stream(%ld-%d): closing with err=%d %s", 
                      session->id, (int)stream->id, (int)error_code,
                      h2_h2_err_description(error_code));
        h2_stream_rst(stream, error_code);
    }
    
    return h2_conn_io_writeb(&session->io,
                             h2_bucket_eos_create(session->c->bucket_alloc, 
                                                  stream));
}

static int on_stream_close_cb(nghttp2_session *ngh2, int32_t stream_id,
                              uint32_t error_code, void *userp)
{
    h2_session *session = (h2_session *)userp;
    h2_stream *stream;
    
    (void)ngh2;
    stream = h2_session_get_stream(session, stream_id);
    if (stream) {
        stream_release(session, stream, error_code);
    }
    return 0;
}

