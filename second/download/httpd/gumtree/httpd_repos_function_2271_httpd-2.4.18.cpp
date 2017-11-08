void h2_stream_cleanup(h2_stream *stream)
{
    h2_session_stream_destroy(stream->session, stream);
    /* stream is gone */
}