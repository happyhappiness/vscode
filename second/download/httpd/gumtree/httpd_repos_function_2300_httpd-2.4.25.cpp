void h2_stream_eos_destroy(h2_stream *stream)
{
    h2_session_stream_done(stream->session, stream);
    /* stream possibly destroyed */
}