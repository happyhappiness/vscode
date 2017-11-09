static void on_stream_event(void *ctx, h2_stream *stream, 
                                  h2_stream_event_t ev)
{
    h2_session *session = ctx;
    switch (ev) {
        case H2_SEV_IN_DATA_PENDING:
            h2_iq_append(session->in_pending, stream->id);
            break;
        default:
            /* NOP */
            break;
    }
}