int h2_stream_needs_submit(const h2_stream *stream)
{
    switch (stream->state) {
        case H2_STREAM_ST_OPEN:
        case H2_STREAM_ST_CLOSED_INPUT:
        case H2_STREAM_ST_CLOSED_OUTPUT:
        case H2_STREAM_ST_CLOSED:
            return !stream->submitted;
        default:
            return 0;
    }
}