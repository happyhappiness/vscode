static apr_status_t stream_end_headers(h2_session *session,
                                       h2_stream *stream, int eos)
{
    (void)session;
    return h2_stream_write_eoh(stream, eos);
}