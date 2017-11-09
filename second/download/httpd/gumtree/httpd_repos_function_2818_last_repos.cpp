static int on_invalid_header_cb(nghttp2_session *ngh2, 
                                const nghttp2_frame *frame, 
                                const uint8_t *name, size_t namelen, 
                                const uint8_t *value, size_t valuelen, 
                                uint8_t flags, void *user_data)
{
    h2_session *session = user_data;
    h2_stream *stream;
    
    if (APLOGcdebug(session->c)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03456)
                      "h2_stream(%ld-%d): invalid header '%s: %s'", 
                      session->id, (int)frame->hd.stream_id,
                      apr_pstrndup(session->pool, (const char *)name, namelen),
                      apr_pstrndup(session->pool, (const char *)value, valuelen));
    }
    stream = h2_session_stream_get(session, frame->hd.stream_id);
    if (stream) {
        h2_stream_rst(stream, NGHTTP2_PROTOCOL_ERROR);
    }
    return 0;
}