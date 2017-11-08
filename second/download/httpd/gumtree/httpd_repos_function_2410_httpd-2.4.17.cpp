h2_stream *h2_session_get_stream(h2_session *session, int stream_id)
{
    AP_DEBUG_ASSERT(session);
    return h2_stream_set_get(session->streams, stream_id);
}