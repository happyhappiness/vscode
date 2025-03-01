static int on_begin_headers_cb(nghttp2_session *ngh2,
                               const nghttp2_frame *frame, void *userp)
{
    h2_session *session = (h2_session *)userp;
    h2_stream *s;
    
    /* We may see HEADERs at the start of a stream or after all DATA
     * streams to carry trailers. */
    (void)ngh2;
    s = h2_session_get_stream(session, frame->hd.stream_id);
    if (s) {
        /* nop */
    }
    else {
        s = h2_session_open_stream((h2_session *)userp, frame->hd.stream_id);
    }
    return s? 0 : NGHTTP2_ERR_START_STREAM_NOT_ALLOWED;
}