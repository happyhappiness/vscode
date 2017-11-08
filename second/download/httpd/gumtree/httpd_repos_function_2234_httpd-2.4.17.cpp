static void set_state(h2_stream *stream, h2_stream_state_t state)
{
    AP_DEBUG_ASSERT(stream);
    if (stream->state != state) {
        stream->state = state;
    }
}