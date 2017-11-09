static void on_stream_state_event(void *ctx, h2_stream *stream, 
                                  h2_stream_event_t ev)
{
    h2_session *session = ctx;
    switch (ev) {
        case H2_SEV_CANCELLED:
            if (session->state != H2_SESSION_ST_DONE) {
                nghttp2_submit_rst_stream(session->ngh2, NGHTTP2_FLAG_NONE, 
                                          stream->id, stream->rst_error);
            }
            break;
        default:
            /* NOP */
            break;
    }
}